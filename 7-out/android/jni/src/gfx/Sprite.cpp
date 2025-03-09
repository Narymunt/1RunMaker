#include "Sprite.h"

// init

CSprite::CSprite(char cFilename[]) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fPositionX(0), _fPositionY(0), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0)
{
	Init(NULL, cFilename);
}

CSprite::CSprite(char cFilename[], int iX, int iY) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0), _fPositionX((float)iX),_fPositionY((float)iY)
{
	Init(NULL, cFilename);
}

// init

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY) :
_pSprite(0), _fRotation(0), _fScaleX(fX), _fScaleY(fY), _fPositionX((float)iX), _fPositionY((float)iY), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0)
{
	Init(NULL, cFilename);
}

// init

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot) :
_pSprite(0), _fRotation(0), _fScaleX(fX), _fScaleY(fY), _fPositionX((float)iX), _fPositionY((float)iY), _fAlfa(1.0f),
_fRotationI(fRot), _ulRenderTime(0)
{
	Init(NULL, cFilename);
}

// init

CSprite::CSprite(char cFilename[], int iX, int iY, float fAlfa) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fPositionX((float)iX), _fPositionY((float)iY), _fAlfa(fAlfa),
_fRotationI(0), _ulRenderTime(0)
{
	Init(NULL, cFilename);
}

// init

CSprite::CSprite(char cFilename[], float fAlfa) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fPositionX(0.0f), _fPositionY(0.0f), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0)
{
	Init(NULL, cFilename);
}

// init

CSprite::CSprite(CScreen *pScreen, char cFilename[]) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fPositionX(0), _fPositionY(0), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0)
{
	Init(pScreen,cFilename);
}

CSprite::CSprite(CScreen *pScreen, char cFilename[], int iX, int iY) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0), _fPositionX((float)iX),_fPositionY((float)iY)
{
	Init(pScreen,cFilename);
}

// init

CSprite::CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY) :
_pSprite(0), _fRotation(0), _fScaleX(fX), _fScaleY(fY), _fPositionX((float)iX), _fPositionY((float)iY), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0)
{
	Init(pScreen,cFilename);
}

// init

CSprite::CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY, float fRot) :
_pSprite(0), _fRotation(0), _fScaleX(fX), _fScaleY(fY), _fPositionX((float)iX), _fPositionY((float)iY), _fAlfa(1.0f),
_fRotationI(fRot), _ulRenderTime(0)
{
	Init(pScreen,cFilename);
}

// init

CSprite::CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fAlfa) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fPositionX((float)iX), _fPositionY((float)iY), _fAlfa(fAlfa),
_fRotationI(0), _ulRenderTime(0)
{
	Init(pScreen,cFilename);
}

// init

CSprite::CSprite(CScreen *pScreen, char cFilename[], float fAlfa) :
_pSprite(0), _fRotation(0), _fScaleX(1.0f), _fScaleY(1.0f), _fPositionX(0.0f), _fPositionY(0.0f), _fAlfa(1.0f),
_fRotationI(0), _ulRenderTime(0)
{
	Init(pScreen, cFilename);
}

// init

void CSprite::Init(CScreen *pScreen, char cFilename[])
{
    SDL_Surface 			*surface;
    SDL_Surface				*pConvertedSurface = NULL;
    GLint 					nOfColors;
    GLenum 					texture_format;
    char					cFilenameExt[200];
    SDL_RWops				*plik=NULL;
	SDL_PixelFormat 		format;

    memset(cFilenameExt,0,200);

    if (pScreen!=NULL)	    	// konwersja z rozdzielczoscia, "plik" = "plik_SDS.png"
    {
    	if (pScreen->_isSDS)
    	{
    		sprintf(cFilenameExt,"%s_SDS.png", cFilename);
    		plik = SDL_RWFromFile(cFilenameExt, "rb");

    		if (!plik)	// jpg zamiast png ?
    		{
        		sprintf(cFilenameExt,"%s_SDS.jpg", cFilename);
        		plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS, bierzemy HDS
    		{
    			sprintf(cFilenameExt,"%s_HDS.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS png, bierzemy HDS jpg
    		{
    			sprintf(cFilenameExt,"%s_HDS.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDS, bierzemy SDW
    		{
    			sprintf(cFilenameExt,"%s_SDW.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW png, bierzemy SDW jpg
    		{
    			sprintf(cFilenameExt,"%s_SDW.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDS, bierzemy HDW
    		{
    			sprintf(cFilenameExt,"%s_HDW.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDS png, bierzemy HDW jpg
    		{
    			sprintf(cFilenameExt,"%s_HDW.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)
    		{
    			SDL_Log("Nie znaleziono pliku : %s\n",cFilename);
    			return;
    		}
    	} // isSDS

    	if (pScreen->_isSDW)
    	{
    		sprintf(cFilenameExt,"%s_SDW.png", cFilename);
    		plik = SDL_RWFromFile(cFilenameExt, "rb");

    		if (!plik)	// jpg zamiast png ?
    		{
    			sprintf(cFilenameExt,"%s_SDW.jpg", cFilename);
        		plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW, bierzemy HDW
    		{
    			sprintf(cFilenameExt,"%s_HDW.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW png, bierzemy HDW jpg
    		{
    			sprintf(cFilenameExt,"%s_HDW.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW, bierzemy SDS
    		{
    			sprintf(cFilenameExt,"%s_SDS.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW png, bierzemy SDS jpg
    		{
    			sprintf(cFilenameExt,"%s_SDS.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW, bierzemy HDS
    		{
    			sprintf(cFilenameExt,"%s_HDS.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma SDW png, bierzemy HDS jpg
    		{
    			sprintf(cFilenameExt,"%s_HDS.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)
    		{
    			SDL_Log("Nie znaleziono pliku : %s\n",cFilename);
    			return;
    		}
    	} // isSDW

    	if (pScreen->_isHDS)
    	{
    		sprintf(cFilenameExt,"%s_HDS.png", cFilename);
    		plik = SDL_RWFromFile(cFilenameExt, "rb");

    		if (!plik)	// jpg zamiast png ?
    		{
        		sprintf(cFilenameExt,"%s_HDS.jpg", cFilename);
        		plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS, bierzemy SDS
    		{
    			sprintf(cFilenameExt,"%s_SDS.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS png, bierzemy HDS jpg
    		{
    			sprintf(cFilenameExt,"%s_SDS.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS, bierzemy HDW
    		{
    			sprintf(cFilenameExt,"%s_HDW.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS png, bierzemy HDW jpg
    		{
    			sprintf(cFilenameExt,"%s_HDW.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS, bierzemy SDW
    		{
    			sprintf(cFilenameExt,"%s_SDW.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDS png, bierzemy SDW jpg
    		{
    			sprintf(cFilenameExt,"%s_SDW.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)
    		{
    			SDL_Log("Nie znaleziono pliku : %s\n",cFilename);
    			return;
    		}
    	} // isHDS

    	if (pScreen->_isHDW)
    	{
    		sprintf(cFilenameExt,"%s_HDW.png", cFilename);
    		plik = SDL_RWFromFile(cFilenameExt, "rb");

    		if (!plik)	// jpg zamiast png ?
    		{
        		sprintf(cFilenameExt,"%s_HDW.jpg", cFilename);
        		plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDW, bierzemy SDW
    		{
    			sprintf(cFilenameExt,"%s_SDW.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDW png, bierzemy SDW jpg
    		{
    			sprintf(cFilenameExt,"%s_SDW.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDW, bierzemy HDS
    		{
    			sprintf(cFilenameExt,"%s_HDS.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDW png, bierzemy HDS jpg
    		{
    			sprintf(cFilenameExt,"%s_HDS.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDW, bierzemy SDS
    		{
    			sprintf(cFilenameExt,"%s_SDS.png", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)	// nie ma HDW png, bierzemy SDS jpg
    		{
    			sprintf(cFilenameExt,"%s_SDS.jpg", cFilename);
    			plik = SDL_RWFromFile(cFilenameExt, "rb");
    		}

    		if (!plik)
    		{
    			SDL_Log("Nie znaleziono pliku : %s\n",cFilename);
    			return;
    		}
    	} // isHDW
    } // pScreen!=NULL
    else	// podana dokladna nazwa pliku nie szukamy assetu wlasciwego dla rozdzielczosci
    {
    	plik = SDL_RWFromFile(cFilename, "rb");
    }

	surface = IMG_Load_RW(plik,1);

	if (!surface)
		SDL_Log("Nie udalo sie utworzyc surface dla %s\n",cFilename);

    // get the number of channels in the SDL surface

	nOfColors = surface->format->BytesPerPixel;

    if (nOfColors == 4)     // contains an alpha channel
    {
        texture_format = GL_RGBA;

    	if (surface->format->Rmask == 0x000000ff)	// big endian
        {
            pScreen ? SDL_Log("GL_RGBA : %s\n",cFilenameExt) : SDL_Log("GL_RGBA : %s\n",cFilename);
        }
        else	// little endian
        {
            pScreen ? SDL_Log("GL_BGRA : %s\n",cFilenameExt) : SDL_Log("GL_BGRA : %s\n",cFilename);

            format = oglGetPixelFormat(GL_RGBA);
        	pConvertedSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, format.Rmask, format.Gmask, format.Bmask, format.Amask);
        	SDL_BlitSurface(surface, NULL, pConvertedSurface, NULL);
        }
    }
    else if (nOfColors == 3)     // no alpha channel
    {
        texture_format = GL_RGBA;

        if (surface->format->Rmask == 0x000000ff)	// big endian
        {
            pScreen ? SDL_Log("GL_RGB : %s\n",cFilenameExt) : SDL_Log("GL_RGB : %s\n",cFilename);

        	format = oglGetPixelFormat(GL_RGBA);
        	pConvertedSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, format.Rmask, format.Gmask, format.Bmask, format.Amask);
        	SDL_BlitSurface(surface, NULL, pConvertedSurface, NULL);
        }
        else	// little endian
        {
            pScreen ? SDL_Log("GL_BGR : %s\n",cFilenameExt) : SDL_Log("GL_BGR : %s\n",cFilename);

            format = oglGetPixelFormat(GL_RGBA);
        	pConvertedSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, format.Rmask, format.Gmask, format.Bmask, format.Amask);
        	SDL_BlitSurface(surface, NULL, pConvertedSurface, NULL);
        }
    }
    else
    {
        printf("warning: the image is not truecolor..  this will probably break\n");
    }

    glGenTextures(1, &_pSprite);

    glBindTexture(GL_TEXTURE_2D, _pSprite);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    if (pConvertedSurface!=NULL)
    {
    	glTexImage2D(GL_TEXTURE_2D, 0, texture_format, pConvertedSurface->w, pConvertedSurface->h, 0, texture_format, GL_UNSIGNED_BYTE, pConvertedSurface->pixels);
    }
    else
    {
    	glTexImage2D(GL_TEXTURE_2D, 0, texture_format, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
    }

	if (!_pSprite)
	{
		printf("ERROR : SPRITE %s not found!\n",cFilename);
	}

	_fOriginalX = (float) surface->w;
	_fOriginalY = (float) surface->h;

	_fSizeX = _fOriginalX;
	_fSizeY = _fOriginalY;

	// incrementators

	SDL_FreeSurface(surface);

	if (pConvertedSurface!=NULL)
		SDL_FreeSurface(pConvertedSurface);
}

// destructor

CSprite::~CSprite()
{
	glDeleteTextures(1, &_pSprite);
}

void CSprite::Render(int x, int y, float a)
{
	Position(x,y);
	_fAlfa = a;
	Render();
}

// render sprite using top left coords

void CSprite::Render(void)
{
	GLfloat hch, hcw;

	glPushMatrix();

	hcw = ((GLfloat)_fOriginalX ) * _fScaleX;
	hch = ((GLfloat)_fOriginalY ) * _fScaleY;

	glRotatef(_fRotation, 0, 0, 1.0f);

	GLfloat box[] = {_fPositionX,_fPositionY+hch,0,_fPositionX+hcw,_fPositionY+hch,0,_fPositionX+hcw,_fPositionY,0,_fPositionX,_fPositionY,0};
	GLfloat tex[] = {0,1, 1,1, 1,0, 0,0};

	glColor4f(1.0f,1.0f,1.0f,_fAlfa);	//rgba
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D,_pSprite);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0,box);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);
	glDrawArrays(GL_TRIANGLE_FAN,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}

// render sprite using middle of texture coords

void CSprite::RenderC(void)
{
	GLfloat hch, hcw;

	glPushMatrix();

	hcw = ((GLfloat)_fOriginalX/2) * _fScaleX;
	hch = ((GLfloat)_fOriginalY/2) * _fScaleY;

	glTranslatef((GLfloat)_fPositionX, (GLfloat)_fPositionY, 0);
	glRotatef(_fRotation, 0, 0, 1.0f);

	GLfloat box[] = {-hcw,hch,0,hcw,hch,0,hcw,-hch,0,-hcw,-hch,0};
	GLfloat tex[] = {0,1, 1,1, 1,0, 0,0};

	glColor4f(1.0f,1.0f,1.0f,_fAlfa);	//rgba
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D,_pSprite);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0,box);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);
	glDrawArrays(GL_TRIANGLE_FAN,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();

}

// updates parameters after rendering

void CSprite::Update(void)
{
	Render();

	_fRotation += _fRotationI;

	_fScaleX += _fScaleXI;
	_fScaleY += _fScaleYI;

	_fPositionX += _fPositionXI;
	_fPositionY += _fPositionYI;

	_fAlfa += _fAlfaI;
}

// updates parameters after rendering, center coords

void CSprite::UpdateC(void)
{
	RenderC();

	_fRotation += _fRotationI;

	_fScaleX += _fScaleXI;
	_fScaleY += _fScaleYI;

	_fPositionX += _fPositionXI;
	_fPositionY += _fPositionYI;

	_fAlfa += _fAlfaI;
}

// set & get scale, update size

void CSprite::Scale(float fX, float fY)
{
	_fScaleX = fX;
	_fScaleY = fY;

	_fSizeX = _fOriginalX * _fScaleX;
	_fSizeY = _fOriginalY * _fScaleY;
}

// aktualizuj parametry i rysuj 

void CSprite::Render(unsigned long ulTimer)
{
	if (_ulRenderTime==0)	// pierwsze rysowanie 
	{
		_isCenter ? UpdateC() : Update();
	}
	else
	{
		_ulDeltaTime = ulTimer - _ulRenderTime;

		_fRotation += (float)(_fRotationI * _ulDeltaTime);

		_fScaleX += (float)(_fScaleXI * _ulDeltaTime);
		_fScaleY += (float)(_fScaleYI * _ulDeltaTime);

		_fPositionX += (float)(_fPositionXI * _ulDeltaTime);
		_fPositionY += (float)(_fPositionYI * _ulDeltaTime);

		_fAlfa += (float)(_fAlfaI * _ulDeltaTime);

		_isCenter ? RenderC() : Render();
	}

	_ulRenderTime = ulTimer;	// zapamietaj kiedy narysowalismy klatke
}

void CSprite::Resize(int x1, int y1, int x2, int y2)
{
	Position((float)x1, (float)y1);
	Scale( (float)(x2-x1)/(float)(_fOriginalX), (float)(y2-y1)/(float)(_fOriginalY) );
}

void CSprite::Fullscreen(CScreen *pScreen)
{
	Resize(0,0,pScreen->_iSizeX, pScreen->_iSizeY);
}

SDL_PixelFormat CSprite::oglGetPixelFormat(GLenum glFormat)
{
	SDL_PixelFormat format;
	if(glFormat == GL_RGBA)
	{
		format.BytesPerPixel = 4;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		format.Rmask = 0xff000000;
		format.Gmask = 0x00ff0000;
		format.Bmask = 0x0000ff00;
		format.Amask = 0x000000ff;
#else
		format.Rmask = 0x000000ff;
		format.Gmask = 0x0000ff00;
		format.Bmask = 0x00ff0000;
		format.Amask = 0xff000000;
#endif
	}
	else
	{
		format.BytesPerPixel = 3;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		format.Rmask = 0xff0000;
		format.Gmask = 0x00ff00;
		format.Bmask = 0x0000ff;
#else
		format.Rmask = 0x0000ff;
		format.Gmask = 0x00ff00;
		format.Bmask = 0xff0000;
#endif
		format.Amask = 0;
	}

	return format;
}

// set & get position

void CSprite::Position(float fX, float fY)
{
	_fPositionX = fX;
	_fPositionY = fY;
}

void CSprite::Color(float r, float g, float b, float a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

void CSprite::Color(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;
}
