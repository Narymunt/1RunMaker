#include "AndroidFile.h"

CAndroidFile::CAndroidFile(char cFilename[]) :
_plik(0), _pBuffer(0), _uiSize(0)
{
	_plik = SDL_RWFromFile(cFilename, "rb");

	if (_plik==NULL)
	{
		SDL_Log("[ERROR] : Nie mozna znalezc pliku: %s\n",cFilename);
	}
}

void CAndroidFile::uiSize(unsigned int i)
{
	if (_pBuffer!=0)
		delete _pBuffer;

	_uiSize = i;

	_pBuffer = new char[_uiSize];
}

void CAndroidFile::Load()
{
	SDL_RWseek(_plik, 0, SEEK_END);
	_uiSize = SDL_RWtell(_plik);
	SDL_RWseek(_plik, 0, SEEK_SET);

	_pBuffer = new char[_uiSize];
	_plik->read(_plik,_pBuffer,_uiSize,1);
}

void CAndroidFile::Save()
{
	SDL_RWseek(_plik, 0, SEEK_SET);
	_plik->write(_plik,_pBuffer,_uiSize,1);
}

CAndroidFile::~CAndroidFile()
{
	SDL_FreeRW(_plik);
	delete []_pBuffer;
}


