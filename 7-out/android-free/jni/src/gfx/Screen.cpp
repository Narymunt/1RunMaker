#include "Screen.h"

CScreen::CScreen() : _window(NULL), _gl(NULL), 
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false),
_isHD(false)
{
    float fx, fy;

	if (SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		printf("ERROR: unable to init sdl video: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GetDisplayMode(0,0,&_mode);

	_iSizeX = _mode.w;
	_iSizeY = _mode.h;

	_fPixelRatio = (float)_iSizeX / (float)_iSizeY;
	_fReverseRatio = (float)_iSizeY / (float)_iSizeX;

	SDL_Log("Screen X: %d Y: %d\n",_iSizeX,_iSizeY);
	SDL_Log("Pixel ratio : %.2f (reverse: %.2f)\n", _fPixelRatio,_fReverseRatio);

	// Samsung fix

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

	// general

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window = SDL_CreateWindow(NULL, 0, 0, _iSizeX, _iSizeY, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

	if (_window == 0)
	{
		SDL_Log("ERROR: Failed to create window.\n");
		SDL_Quit();
		return;
	}
	else
    {
        SDL_Log("Screen : %d x %d\n", _iSizeX, _iSizeY);        
    }

	_gl = SDL_GL_CreateContext(_window);

	glViewport(0, 0, _iSizeX, _iSizeY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glOrthof(0.0f, _iSizeX, _iSizeY, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDisable(GL_DEPTH_TEST);

	// wyliczanie punktow dla siatki 100x100

    fx = (float)_iSizeX * 0.01f;
    fy = (float)_iSizeY * 0.01f;

    for (int i=0; i<101; i++)
    {
        float f;
        
        f = fx * (float)i;
        _iGridX[i] = (int)f;
        
        f = fy * (float)i;
        _iGridY[i] = (int)f;
    }

	SDL_Log("Screen TILE X: %.2f Y: %.2f\n",fx,fy);

	// sprawdzenie typu ekranu

    if (_iSizeX < 1500)
    {
    	if (_fPixelRatio > _fReverseRatio)
    	{
    		(_fPixelRatio < 1.5f) ? _isSDS = true : _isSDW = true;
    	}
    	else
    	{
    		(_fReverseRatio < 1.5f) ? _isSDS = true : _isSDW = true;
    	}
    }
    else
    {
    	if (_fPixelRatio > _fReverseRatio)
    	{
    		(_fPixelRatio < 1.5f) ? _isHDS = true : _isHDW = true;
    	}
    	else
    	{
    		(_fReverseRatio < 1.5f) ? _isHDS = true : _isHDW = true;
    	}

    	_isHD = true;
    }

    if (_isSDS) SDL_Log("Resolution : SDS\n");
    if (_isSDW) SDL_Log("Resolution : SDW\n");
    if (_isHDS) SDL_Log("Resolution : HDS\n");
    if (_isHDW) SDL_Log("Resolution : HDW\n");

	precalc();
}

CScreen::~CScreen()
{
	SDL_GL_DeleteContext(_gl);
    SDL_DestroyWindow(_window);
}

void CScreen::Clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You have to do this each frame, because SDL messes up with your GL context when drawing on-screen keyboard, however is saves/restores your matrices
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
     glEnable(GL_TEXTURE_2D);
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void CScreen::Flip(void)
{
	SDL_GL_SwapWindow(_window);
}

/**
   Przygotuj tablice przeliczeniowe.
*/

void CScreen::precalcTableX(int size, int *table)
{
	float index, pixelSize;

	index = 0; pixelSize = _iSizeX / (float)size; _pixelX = pixelSize;

	for (int i = 0; i<size; i++)
	{
		table[i] = (int)index;
		index += pixelSize;
	}
}

void CScreen::precalcTableY(int size, int *table)
{
	float index, pixelSize;

	index = 0; pixelSize = _iSizeY / (float)size; _pixelY = pixelSize;

	for (int i = 0; i<size; i++)
	{
		table[i] = (int)index;
		index += pixelSize;
	}
}


void CScreen::precalc(void)
{
	precalcTableX(1920, _xHDW); precalcTableY(1080, _yHDW);
	precalcTableX(2048, _xHDS); precalcTableY(1536, _yHDS);
	precalcTableX(1366, _xSDW); precalcTableY(768, _ySDW);
	precalcTableX(1024, _xSDS); precalcTableY(768, _ySDS);
}

/**
   Zwraca rozmiar pixela.
   @return rozmiar ekranu / aktualne wymiary zrodlowe
*/

float CScreen::pixelX(void)
{
   if (_isSDS) return (float)_iSizeX/1024.0f;
   if (_isSDW) return (float)_iSizeX/1366.0f;
   if (_isHDS) return (float)_iSizeX/2048.0f;
   if (_isHDW) return (float)_iSizeX/1920.0f;
}

/**
   Zwraca rozmiar pixela.
   @return rozmiar ekranu / aktualne wymiary zrodlowe
*/

float CScreen::pixelY(void)
{
   if (_isSDS) return (float)_iSizeY/768.0f;
   if (_isSDW) return (float)_iSizeY/768.0f;
   if (_isHDS) return (float)_iSizeY/1536.0f;
   if (_isHDW) return (float)_iSizeY/1080.0f;

}

/**
   Zwraca rzeczywist¹ wspó³rzêdn¹ na ekranie, gdy operujemy na fikcyjnych liczbach.
   @param x gdzie na ekranie chcemy postawiæ pixel
   @return gdzie naprawde postawimy pixel
*/

int CScreen::x(int x)
{
   if (_isSDS) return _xSDS[x];
   if (_isSDW) return _xSDW[x];
   if (_isHDS) return _xHDS[x];
   if (_isHDW) return _xHDW[x];
}

/**
   Zwraca rzeczywist¹ wspó³rzêdn¹ na ekranie, gdy operujemy na fikcyjnych liczbach.
   @param y gdzie na ekranie chcemy postawiæ pixel
   @return gdzie naprawde postawimy pixel
*/

int CScreen::y(int y)
{
   if (_isSDS) return _ySDS[y];
   if (_isSDW) return _ySDW[y];
   if (_isHDS) return _yHDS[y];
   if (_isHDW) return _yHDW[y];
}

int CScreen::perX(float f)
{
	float x;
	x = (float)_iSizeX *(100.0f / f);
	return (int)x;
}

int CScreen::perY(float f)
{
	float y;
	y = (float)_iSizeY *(100.0f / f);
	return (int)y;
}

