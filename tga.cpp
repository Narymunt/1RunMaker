#include "tga.h"

CTGA::CTGA(char f[]) : _sizeX(0), _sizeY(0), _bpp(0), _buffer(0), _sprite(0)
{
	FILE *file;

	if ((file = fopen(f,"rb")) == NULL)
	{
		printf("ERROR: no file %s\n", f);
		return;
	}

	fread(_header, 18, 1, file);

	_sizeX = (unsigned int)(_header[13] << 8) + _header[12];
	_sizeY = (unsigned int)(_header[15] << 8) + _header[14];

	_bpp = _header[16];
	_size = _sizeX * _sizeY*4; 

	if (_bpp == 24)
	{
		unsigned char *tmp = new unsigned char[_sizeX*_sizeY * 3];
		fread(tmp, _sizeX*_sizeY * 3, 1, file);
		_buffer = new unsigned char[_size];

		// konwersja

		for (int i = 0; i < _sizeX*_sizeY; i++)
		{
			_buffer[i * 4] = tmp[i * 3];
			_buffer[i * 4+1] = tmp[i * 3+1];
			_buffer[i * 4+2] = tmp[i * 3+2];
			_buffer[i * 4+3] = 255;
		}
		delete[] tmp;
	}
	else
	{
		_buffer = new unsigned char[_size];
		fread(_buffer, _size, 1, file);
	}

	_centerX = _sizeX / 2;
	_centerY = _sizeY / 2;

	fclose(file);
}

CTGA::CTGA(unsigned long x, unsigned long y) : _sizeX(x), _sizeY(y), _bpp(32), _buffer(0), _sprite(0)
{
	_size = _sizeX * _sizeY * 4;

	_buffer = new unsigned char[_size];
	memset(_buffer, 0, _size);

	_centerX = _sizeX / 2;
	_centerY = _sizeY / 2;
}


CTGA::~CTGA()
{
	delete[]  _buffer;

	if (_sprite)
		delete[] _sprite;

}

void CTGA::save(char f[])
{
	FILE *file;

	if ((file = fopen(f, "wb")) == NULL)
	{
		printf("ERROR: no file %s\n", f);
		return;
	}

	for (int i = 0; i < 17; i++)
		_header[i] = 0;

	_header[2] = 2;

	_header[13] = _sizeX >> 8;	_header[12] = _sizeX & 0xff;
	_header[15] = _sizeY >> 8;	_header[14] = _sizeY & 0xff;
	_header[16] = _header[17] = 32;

	_size = _sizeX * _sizeY * 4;

	fwrite(_header, 18, 1, file);
	fwrite(_buffer, _size, 1, file);

	fclose(file);
}

void CTGA::saveSprite(char f[])
{
	FILE *file;

	if ((file = fopen(f, "wb")) == NULL)
	{
		printf("ERROR: no file %s\n", f);
		return;
	}

	for (int i = 0; i < 17; i++)
		_header[i] = 0;

	_header[2] = 2;

	_header[13] = _spriteSizeX >> 8;	_header[12] = _spriteSizeX & 0xff;
	_header[15] = _spriteSizeY >> 8;	_header[14] = _spriteSizeY & 0xff;
	_header[16] = _header[17] = 32;

	_spriteSize = _spriteSizeX * _spriteSizeY * 4;

	fwrite(_header, 18, 1, file);
	fwrite(_sprite, _spriteSize, 1, file);

	fclose(file);
}

void CTGA::cleanAlfa()
{
	unsigned char r, g, b, a;

	for (unsigned long i = 0; i < _size/4; i++)
	{
		r = _buffer[i * 4];
		g = _buffer[i * 4 + 1];
		b = _buffer[i * 4 + 2];
		a = _buffer[i * 4 + 3];

		if (a == 0)
		{
			_buffer[i * 4] = 0;		//r
			_buffer[i * 4 + 1] = 0; // g
			_buffer[i * 4 + 2] = 0; //b
		}

	}
}

void CTGA::clip()
{
	bool u = false, d = false;

	_x1 = _y1 = 0;
	_x2 = _sizeX;
	_y2 = _sizeY;

	unsigned char r, g, b, a;

	// od góry x1,y1

	for (unsigned long y = 0; y < _sizeY; y++)
	{
		for (unsigned long x = 0; x < _sizeX; x++)
		{
			r = _buffer[ ((_sizeX*4)*y)  + (x * 4)];   // (sizex*y)+x
			g = _buffer[((_sizeX * 4)*y) + (x * 4)+1];   // (sizex*y)+x
			b = _buffer[((_sizeX * 4)*y) + (x * 4)+2];   // (sizex*y)+x
			a = _buffer[((_sizeX * 4)*y) + (x * 4)+3];   // (sizex*y)+x

			if (r != 0 || g != 0 || b != 0 || a != 0)
			{			
				if (u == false)	// wpisujemy tylko raz
				{
					_x1 = x;
					_y1 = y;
					u = true;
				}
				else
				{
					if (x < _x1)
						_x1 = x;
				}
			}

		}
	}

	// od do³u x2,y2

	for (unsigned long y = _sizeY-1; y !=0; y--)
	{
		for (unsigned long x = _sizeX-1; x !=0; x--)
		{
			r = _buffer[((_sizeX * 4)*y) + (x * 4)];   // (sizex*y)+x
			g = _buffer[((_sizeX * 4)*y) + (x * 4) + 1];   // (sizex*y)+x
			b = _buffer[((_sizeX * 4)*y) + (x * 4) + 2];   // (sizex*y)+x
			a = _buffer[((_sizeX * 4)*y) + (x * 4) + 3];   // (sizex*y)+x

			if (r != 0 || g != 0 || b != 0 || a != 0)
			{
				if (d == false)	// wpisujemy tylko raz
				{
					_x2 = x;
					_y2 = y;
					d = true;
				}
				else
				{
					if (x > _x2)
						_x2 = x;
				}
			}
		}
	}

	_spriteSizeX = _x2 - _x1;
	_spriteSizeY = _y2 - _y1;

	_spriteSize = _spriteSizeX * _spriteSizeY * 4;

	if (_sprite != 0)
		delete[]_sprite;

	_sprite = new unsigned char[_spriteSize];

	for (unsigned long y = 0; y < _spriteSizeY; y++)
	{
		for (unsigned long x = 0; x < _spriteSizeX; x++)
		{
			_sprite[((_spriteSizeX * 4)*y) + (x * 4)] = _buffer[((_sizeX * 4)*(y + _y1)) + ((x + _x1) * 4)];    
			_sprite[((_spriteSizeX * 4)*y) + (x * 4) + 1]= _buffer[((_sizeX * 4)*(y + _y1)) + ((x + _x1) * 4)+1];   
			_sprite[((_spriteSizeX * 4)*y) + (x * 4) + 2] = _buffer[((_sizeX * 4)*(y + _y1)) + ((x + _x1) * 4)+2];   
			_sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3] = _buffer[((_sizeX * 4)*(y + _y1)) + ((x + _x1) * 4)+3];   

		}
	}

	_spriteCenterX = _spriteSizeX / 2;
	_spriteCenterY = _spriteSizeY / 2;
}

void CTGA::renderSprite(unsigned char *buffer, unsigned long sizeX, unsigned long sizeY)
{
	for (unsigned long y = 0; y < _spriteSizeY; y++)
	{
		for (unsigned long x = 0; x < _spriteSizeX; x++)
		{
			buffer[((sizeX * 4)*y) + (x * 4)] = _sprite[((_spriteSizeX * 4)*y) + (x * 4)];
			buffer[((sizeX * 4)*y) + (x * 4) + 1] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 1];
			buffer[((sizeX * 4)*y) + (x * 4) + 2] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 2];
			buffer[((sizeX * 4)*y) + (x * 4) + 3] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3]; //alfa
		}
	}
}

void CTGA::renderSprite(unsigned long X, unsigned long Y, unsigned char *buffer, unsigned long sizeX, unsigned long sizeY)
{
	for (unsigned long y = 0; y < _spriteSizeY; y++)
	{
		for (unsigned long x = 0; x < _spriteSizeX; x++)
		{
			if (buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4)] == 0 &&
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 1] == 0 &&
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 2] == 0 &&
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3] == 0)
			{
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4)] = _sprite[((_spriteSizeX * 4)*y) + (x * 4)];
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 1] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 1];
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 2] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 2];
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3]; // alfa
			}
			else
			{
				unsigned long color;

				if (_sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3] >8)
				{
					buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4)] = _sprite[((_spriteSizeX * 4)*y) + (x * 4)];
					buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 1] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 1];
					buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 2] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 2];
					buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3] = _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3]; // alfa
				}

/*
				color = (buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4)] * buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3]) + (_sprite[((_spriteSizeX * 4)*y) + (x * 4)] * _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3]);
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4)] = (unsigned char)(color>>8);

				color = (buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 1] * buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3]) + (_sprite[((_spriteSizeX * 4)*y) + (x * 4) + 1] * _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3]);
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 1] = (unsigned char)(color>>8);

				color = (buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 2] * buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3]) + (_sprite[((_spriteSizeX * 4)*y) + (x * 4) + 2] * _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3]);
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 2] = (unsigned char)(color>>8);

				color = buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3] + _sprite[((_spriteSizeX * 4)*y) + (x * 4) + 3];
				buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4) + 3] = color / 2;
*/

			}
		}
	}
}

void CTGA::renderChannel(unsigned char *buffer, unsigned long sizeX, unsigned long sizeY)
{
	int X = 0;
	int Y = 0;

	for (unsigned long y = 0; y < sizeY; y++)
	{
		for (unsigned long x = 0; x < sizeX; x++)
		{
			if (buffer[((sizeX * 4)*(Y + y)) + ((x + X) * 4)+2] != 0) //r
			{
				buffer[((sizeX * 4)*y) + (x * 4)] = _buffer[((_sizeX * 4)*y) + (x * 4)];
				buffer[((sizeX * 4)*y) + (x * 4) + 1] = _buffer[((_sizeX * 4)*y) + (x * 4) + 1];
				buffer[((sizeX * 4)*y) + (x * 4) + 2] = _buffer[((_sizeX * 4)*y) + (x * 4) + 2];
				buffer[((sizeX * 4)*y) + (x * 4) + 3] = _buffer[((_sizeX * 4)*y) + (x * 4) + 3]; //alfa
			}
		}
	}
}


bool CTGA::isFit(unsigned long x, unsigned long y)	// czy obrazek miesci sie w tych wymiarach
{
	return _sizeX < x && _sizeY < y ? true : false;
}

bool CTGA::isSpriteFit(unsigned long x, unsigned long y)	// czy sprite miesci sie w tych wymiarach
{
	return _spriteSizeX < x && _spriteSizeY < y ? true : false;
}

void CTGA::resize(double f)			// zmiana rozmiaru obrazu
{
	unsigned long newX, newY, newSize;
	unsigned char *newBuffer = 0;
	double deltaX, deltaY;
	unsigned long bufferX, bufferY;

	newX = (unsigned long)((double)_sizeX * f);
	newY = (unsigned long)((double)_sizeY * f);

	newSize = newX * newY * 4;

	newBuffer = new unsigned char[newSize];

	deltaX = (double)_sizeX / (double)newX;
	deltaY = (double)_sizeY/ (double)newY;

	double dy = 0.0f;
	double dx = 0.0f;

	for (unsigned long y = 0 ; y < newY; y++, dy+=deltaY)
	{
		dx = 0.0f;
		for (unsigned long x = 0 ; x < newX; x++, dx+=deltaX)
		{
			bufferX = dx; bufferY = dy;

			newBuffer[((newX * 4)*y) + (x*4)] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4)];
			newBuffer[((newX * 4)*y) + (x * 4)+1] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4)+1];
			newBuffer[((newX * 4)*y) + (x * 4)+2] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4)+2];
			newBuffer[((newX * 4)*y) + (x * 4)+3] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4)+3];
		}
	}

	delete[] _buffer;

	_buffer = new unsigned char[newSize];
	memcpy(_buffer, newBuffer, newSize);

	_sizeX = newX; _sizeY = newY;
	_size = newSize;

	_centerX = _sizeX / 2;
	_centerY = _sizeY / 2;

	delete[] newBuffer;

}

void CTGA::resizeSprite(double f)	// zmiana rozmiaru sprite
{
	unsigned long newX, newY, newSize;
	unsigned char *newBuffer = 0;
	double deltaX, deltaY;
	unsigned long bufferX, bufferY;

	newX = (unsigned long)((double)_spriteSizeX * f);
	newY = (unsigned long)((double)_spriteSizeY * f);

	newSize = newX * newY * 4;

	newBuffer = new unsigned char[newSize];

	deltaX = (double)_spriteSizeX / (double)newX;
	deltaY = (double)_spriteSizeY / (double)newY;

	double dy = 0.0f;
	double dx = 0.0f;

	for (unsigned long y = 0; y < newY; y++, dy += deltaY)
	{
		dx = 0.0f;
		for (unsigned long x = 0; x < newX; x++, dx += deltaX)
		{
			bufferX = dx; bufferY = dy;

			newBuffer[((newX * 4)*y) + (x * 4)] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4)];
			newBuffer[((newX * 4)*y) + (x * 4) + 1] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 1];
			newBuffer[((newX * 4)*y) + (x * 4) + 2] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 2];
			newBuffer[((newX * 4)*y) + (x * 4) + 3] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 3];
		}
	}

	delete[] _sprite;

	_sprite= new unsigned char[newSize];
	memcpy(_sprite, newBuffer, newSize);

	_spriteSizeX = newX; _spriteSizeY = newY;
	_spriteSize = newSize;

	_spriteCenterX = _spriteSizeX / 2;
	_spriteCenterY = _spriteSizeY / 2;

	delete[] newBuffer;
}

void CTGA::resize(double fx, double fy) // zmiana rozmiaru obrazu
{
	unsigned long newX, newY, newSize;
	unsigned char *newBuffer = 0;
	double deltaX, deltaY;
	unsigned long bufferX, bufferY;

	newX = (unsigned long)((double)_sizeX * fx);
	newY = (unsigned long)((double)_sizeY * fy);

	newSize = newX * newY * 4;

	newBuffer = new unsigned char[newSize];

	deltaX = (double)_sizeX / (double)newX;
	deltaY = (double)_sizeY / (double)newY;

	double dy = 0.0f;
	double dx = 0.0f;

	for (unsigned long y = 0; y < newY; y++, dy += deltaY)
	{
		dx = 0.0f;
		for (unsigned long x = 0; x < newX; x++, dx += deltaX)
		{
			bufferX = dx; bufferY = dy;

			newBuffer[((newX * 4)*y) + (x * 4)] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4)];
			newBuffer[((newX * 4)*y) + (x * 4) + 1] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4) + 1];
			newBuffer[((newX * 4)*y) + (x * 4) + 2] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4) + 2];
			newBuffer[((newX * 4)*y) + (x * 4) + 3] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4) + 3];
		}
	}

	delete[] _buffer;

	_buffer = new unsigned char[newSize];
	memcpy(_buffer, newBuffer, newSize);

	_sizeX = newX; _sizeY = newY;
	_size = newSize;

	_centerX = _sizeX / 2;
	_centerY = _sizeY / 2;

	delete[] newBuffer;
}

void CTGA::resizeSprite(double fx, double fy) // zmiara rozmiaru sprite
{
	unsigned long newX, newY, newSize;
	unsigned char *newBuffer = 0;
	double deltaX, deltaY;
	unsigned long bufferX, bufferY;

	newX = (unsigned long)((double)_spriteSizeX * fx);
	newY = (unsigned long)((double)_spriteSizeY * fy);

	newSize = newX * newY * 4;

	newBuffer = new unsigned char[newSize];

	deltaX = (double)_spriteSizeX / (double)newX;
	deltaY = (double)_spriteSizeY / (double)newY;

	double dy = 0.0f;
	double dx = 0.0f;

	for (unsigned long y = 0; y < newY; y++, dy += deltaY)
	{
		dx = 0.0f;
		for (unsigned long x = 0; x < newX; x++, dx += deltaX)
		{
			bufferX = dx; bufferY = dy;

			newBuffer[((newX * 4)*y) + (x * 4)] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4)];
			newBuffer[((newX * 4)*y) + (x * 4) + 1] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 1];
			newBuffer[((newX * 4)*y) + (x * 4) + 2] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 2];
			newBuffer[((newX * 4)*y) + (x * 4) + 3] = _sprite[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 3];
		}
	}

	delete[] _sprite;

	_sprite = new unsigned char[newSize];
	memcpy(_sprite, newBuffer, newSize);

	_spriteSizeX = newX; _spriteSizeY = newY;
	_spriteSize = newSize;

	_spriteCenterX = _spriteSizeX / 2;
	_spriteCenterY = _spriteSizeY / 2;

	delete[] newBuffer;
}

void CTGA::resizeTo(unsigned long nx, unsigned long ny)	// przeskaluj obraz do wymiaru
{
	unsigned long newX, newY, newSize;
	unsigned char *newBuffer = 0;
	double deltaX, deltaY;
	unsigned long bufferX, bufferY;

	newX = nx;
	newY = ny;

	newSize = newX * newY * 4;

	newBuffer = new unsigned char[newSize];

	deltaX = (double)_sizeX / (double)newX;
	deltaY = (double)_sizeY / (double)newY;

	double dy = 0.0f;
	double dx = 0.0f;

	for (unsigned long y = 0; y < newY; y++, dy += deltaY)
	{
		dx = 0.0f;
		for (unsigned long x = 0; x < newX; x++, dx += deltaX)
		{
			bufferX = dx; bufferY = dy;

			newBuffer[((newX * 4)*y) + (x * 4)] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4)];
			newBuffer[((newX * 4)*y) + (x * 4) + 1] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4) + 1];
			newBuffer[((newX * 4)*y) + (x * 4) + 2] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4) + 2];
			newBuffer[((newX * 4)*y) + (x * 4) + 3] = _buffer[((_sizeX * 4)*bufferY) + (bufferX * 4) + 3];
		}
	}

	delete[] _buffer;

	_buffer = new unsigned char[newSize];
	memcpy(_buffer, newBuffer, newSize);

	_sizeX = newX; _sizeY = newY;
	_size = newSize;

	_centerX = _sizeX / 2;
	_centerY = _sizeY / 2;

	delete[] newBuffer;
}

void CTGA::resizeSpriteTo(unsigned long nx, unsigned long ny) // przeskaluj sprite do wymiaru
{
	unsigned long newX, newY, newSize;
	unsigned char *newBuffer = 0;
	double deltaX, deltaY;
	unsigned long bufferX, bufferY;

	newX = nx;
	newY = ny;

	newSize = newX * newY * 4;

	newBuffer = new unsigned char[newSize];

	deltaX = (double)_spriteSizeX / (double)newX;
	deltaY = (double)_spriteSizeY / (double)newY;

	double dy = 0.0f;
	double dx = 0.0f;

	for (unsigned long y = 0; y < newY; y++, dy += deltaY)
	{
		dx = 0.0f;
		for (unsigned long x = 0; x < newX; x++, dx += deltaX)
		{
			bufferX = dx; bufferY = dy;

			newBuffer[((newX * 4)*y) + (x * 4)] = _buffer[((_spriteSizeX * 4)*bufferY) + (bufferX * 4)];
			newBuffer[((newX * 4)*y) + (x * 4) + 1] = _buffer[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 1];
			newBuffer[((newX * 4)*y) + (x * 4) + 2] = _buffer[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 2];
			newBuffer[((newX * 4)*y) + (x * 4) + 3] = _buffer[((_spriteSizeX * 4)*bufferY) + (bufferX * 4) + 3];
		}
	}

	delete[] _sprite;

	_sprite = new unsigned char[newSize];
	memcpy(_sprite, newBuffer, newSize);

	_spriteSizeX = newX; _spriteSizeY = newY;
	_spriteSize = newSize;

	_spriteCenterX = _spriteSizeX / 2;
	_spriteCenterY = _spriteSizeY / 2;

	delete[] newBuffer;

}


void CTGA::flipV()	// zamienia do góry nogami
{
	unsigned char *newBuffer;

	newBuffer = new unsigned char[_size];

	for (unsigned long y = 0; y < _sizeY; y++)
	{
		for (unsigned long x = 0; x < _sizeX; x++)
		{
			newBuffer[((_sizeX * 4)*y) + (x * 4)] = _buffer[((_sizeX * 4)*(_sizeY-y-1)) + (x * 4)];   // (sizex*y)+x
			newBuffer[((_sizeX * 4)*y) + (x * 4) + 1] = _buffer[((_sizeX * 4)*(_sizeY - y - 1)) + (x * 4) + 1];   // (sizex*y)+x
			newBuffer[((_sizeX * 4)*y) + (x * 4) + 2] = _buffer[((_sizeX * 4)*(_sizeY - y - 1)) + (x * 4) + 2];   // (sizex*y)+x
			newBuffer[((_sizeX * 4)*y) + (x * 4) + 3] = _buffer[((_sizeX * 4)*(_sizeY - y - 1)) + (x * 4) + 3];   // (sizex*y)+x
		}
	}

	memcpy(_buffer, newBuffer, _size);

	delete[] newBuffer;


}

void CTGA::dark(unsigned char l)		// zrob ciemniejszy obraz
{
	int t;
	for (unsigned long i = 0; i < l; i++)
	{
		for (unsigned long y = 0; y < _sizeY; y++)
		{
			for (unsigned long x = 0; x < _sizeX; x++)
			{
				if (_buffer[((_sizeX * 4)*y) + (x * 4)] > 0)
				{
					t = (unsigned char)_buffer[((_sizeX * 4)*y) + (x * 4)] - 1;
					t >= 0 ? _buffer[((_sizeX * 4)*y) + (x * 4)] = (unsigned char)t : _buffer[((_sizeX * 4)*y) + (x * 4)] = 0;
				}

				if (_buffer[((_sizeX * 4)*y) + (x * 4)+1] > 0)
				{
					t = (unsigned char)_buffer[((_sizeX * 4)*y) + (x * 4)+1] - 1;
					t >= 0 ? _buffer[((_sizeX * 4)*y) + (x * 4)+1] = (unsigned char)t : _buffer[((_sizeX * 4)*y) + (x * 4)+1] = 0;
				}

				if (_buffer[((_sizeX * 4)*y) + (x * 4)+2] > 0)
				{
					t = (unsigned char)_buffer[((_sizeX * 4)*y) + (x * 4)+2] - 1;
					t >= 0 ? _buffer[((_sizeX * 4)*y) + (x * 4)+2] = (unsigned char)t : _buffer[((_sizeX * 4)*y) + (x * 4)+2] = 0;
				}


			}
		}
	}
}

void CTGA::light(unsigned char l)	// zrob jasniejszy obraz
{
	int t;
	for (unsigned long y = 0; y < _sizeY; y++)
	{
		for (unsigned long x = 0; x < _sizeX; x++)
		{
			if (_buffer[((_sizeX * 4)*y) + (x * 4)] <255)
			{
				t = (unsigned char)_buffer[((_sizeX * 4)*y) + (x * 4)]+l;
				t <= 255 ? _buffer[((_sizeX * 4)*y) + (x * 4)] = (unsigned char)t : _buffer[((_sizeX * 4)*y) + (x * 4)] = 255;
			}
		}
	}

}

void CTGA::grey(unsigned char l) // usrednij kolory
{
	int t;
	
	for (int i = 0; i < l; i++)
	{
		for (unsigned long y = 0; y < _sizeY; y++)
		{
			for (unsigned long x = 0; x < _sizeX; x++)
			{
				{
					//rgba
					t = _buffer[((_sizeX * 4)*y) + (x * 4)] + _buffer[((_sizeX * 4)*y) + (x * 4) + 1] + _buffer[((_sizeX * 4)*y) + (x * 4) + 2];
					_buffer[((_sizeX * 4)*y) + (x * 4)] = _buffer[((_sizeX * 4)*y) + (x * 4) + 1] = _buffer[((_sizeX * 4)*y) + (x * 4) + 2] = (unsigned char)t / 3;
				}
			}
		}
	}
}

void CTGA::blur(unsigned char l) // usrednij kolory
{
	int tr,tg,tb,ta;
	int div;

	for (int i = 0; i < l; i++)
	{
		for (unsigned long y = 0; y < _sizeY; y++)
		{
			for (unsigned long x = 0; x < _sizeX; x++)
			{
				{
					div = 1;
					tr = _buffer[((_sizeX * 4)*y) + (x * 4)];
					tg = _buffer[((_sizeX * 4)*y) + (x * 4) + 1];
					tb = _buffer[((_sizeX * 4)*y) + (x * 4) + 2];
					ta = _buffer[((_sizeX * 4)*y) + (x * 4) + 3];

					if (x < _sizeX - 1) // prawa
					{
						tr += _buffer[((_sizeX * 4)*y) + ((x + 1) * 4)];
						tg += _buffer[((_sizeX * 4)*y) + ((x + 1) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*y) + ((x + 1) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*y) + ((x + 1) * 4) + 3];
						div++;
					}

					if (x > 0) // lewa
					{
						tr += _buffer[((_sizeX * 4)*y) + ((x - 1) * 4)];
						tg += _buffer[((_sizeX * 4)*y) + ((x - 1) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*y) + ((x - 1) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*y) + ((x - 1) * 4) + 3];
						div++;
					}

					if (y < _sizeY - 1) // dolny
					{
						tr += _buffer[((_sizeX * 4)*(y + 1)) + ((x) * 4)];
						tg += _buffer[((_sizeX * 4)*(y + 1)) + ((x) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*(y + 1)) + ((x) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*(y + 1)) + ((x) * 4) + 3];
						div++;
					}

					if (y > 0) // górny
					{
						tr += _buffer[((_sizeX * 4)*(y - 1)) + ((x) * 4)];
						tg += _buffer[((_sizeX * 4)*(y - 1)) + ((x) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*(y - 1)) + ((x) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*(y - 1)) + ((x) * 4) + 3];
						div++;
					}

					if (x > 0 && y > 0) // lewy górny
					{
						tr += _buffer[((_sizeX * 4)*(y - 1)) + ((x - 1) * 4)];
						tg += _buffer[((_sizeX * 4)*(y - 1)) + ((x - 1) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*(y - 1)) + ((x - 1) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*(y - 1)) + ((x - 1) * 4) + 3];
						div++;
					}

					if (x < _sizeX - 1 && y > 0) // prawy górny
					{
						tr += _buffer[((_sizeX * 4)*(y - 1)) + ((x + 1) * 4)];
						tg += _buffer[((_sizeX * 4)*(y - 1)) + ((x + 1) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*(y - 1)) + ((x + 1) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*(y - 1)) + ((x + 1) * 4) + 3];
						div++;
					}

					if (x > 0 && y < _sizeY - 1) // lewy dolny
					{
						tr += _buffer[((_sizeX * 4)*(y + 1)) + ((x - 1) * 4)];
						tg += _buffer[((_sizeX * 4)*(y + 1)) + ((x - 1) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*(y + 1)) + ((x - 1) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*(y + 1)) + ((x - 1) * 4) + 3];
						div++;
					}

					if (x < _sizeX - 1 && y < _sizeY - 1) // prawy dolny
					{
						tr += _buffer[((_sizeX * 4)*(y + 1)) + ((x + 1) * 4)];
						tg += _buffer[((_sizeX * 4)*(y + 1)) + ((x + 1) * 4) + 1];
						tb += _buffer[((_sizeX * 4)*(y + 1)) + ((x + 1) * 4) + 2];
						ta += _buffer[((_sizeX * 4)*(y + 1)) + ((x + 1) * 4) + 3];
						div++;
					}

					//rgba
					_buffer[((_sizeX * 4)*y) + (x * 4)] = (unsigned char)(tr / div);
					_buffer[((_sizeX * 4)*y) + (x * 4) + 1] = (unsigned char)(tg / div);
					_buffer[((_sizeX * 4)*y) + (x * 4) + 2] = (unsigned char)(tb / div);

				}
			}
		}
	}
}

void CTGA::darkSprite(unsigned char l)		// zrob ciemniejszy obraz
{

}

void CTGA::lightSprite(unsigned char l)	// zrob jasniejszy obraz
{

}

void CTGA::greySprite() // usrednij kolory
{

}

void CTGA::blurSprite()
{

}

void CTGA::setA(unsigned char a)	// alfa = a dla ka¿dego pixela
{
	for (unsigned long y = 0; y < _sizeY; y++)
	{
		for (unsigned long x = 0; x < _sizeX; x++)
		{
			_buffer[((_sizeX * 4)*y) + (x * 4) + 3] = a;
		}
	}
}

void CTGA::setA(unsigned char a, unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2)
{
	for (unsigned long y = y1; y < y2; y++)
	{
		for (unsigned long x = x1; x < x2; x++)
		{
			_buffer[((_sizeX * 4)*y) + (x * 4) + 3] = a;
		}
	}

}
