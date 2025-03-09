// konfiguracja ekranu urzadzenia
// SDS = soft def. square = dla rozdzielczosci <1500px przy pixel ratio < 1.5 (kwadratowe, np. 1024x768)
// SDW = soft def. wide = dla rozdzielczosci <1500px przy pixel ratio >1.5 (szerokie np. 1366x768, 1280x600)
// HDS = high def. square = dla rozdzielczosci >=1500px przy pixel ratio >1.5 (kwadratowe np. 2048x1536)
// HDW = high def. square = dla rozdzielczosci >=1500px przy pidel ratio > 1.5 (szerowkie np. 1920x1080)
//
// rozdzielczosci bazowe
// SDS - 1024x768
// SDW - 1366x768
// HDS - 2048x1536
// HDW - 1920x1080

#pragma once

#include <vector>
#include "SDL.h"
#include "OGL.h"

class CScreen
{

public : 

	CScreen();								// init screen with desktop resolution
	~CScreen();

	void			Clear(void);
	void			Flip(void);

	int		x(int x);			// autodetekcja aktualnej rozdzielczosci i tablicy przeliczeniowej
	int		y(int y);			// podaje zwrotny parametr dla podanego pixela, samemu trzeba pamietac o limitach

	int		perX(float f);		// wspó³rzêdne ekranu w skali 0.0f-100.0f
	int		perY(float f);		// to operuje na rzeczywistych wymiarach ekranu

	void	precalc(void);		// prepare precalc tables
	void	precalcTableX(int size, int *table);	// pomocnicza
	void	precalcTableY(int size, int *table);	// pomocnicza

	float	pixelX(void);		// X pixel size
	float	pixelY(void);		// y pixel size

	int		_xHDW[1920], _yHDW[1080];	// _xHDW = _iSizeX, _yHDW = _iSizeY
	int		_xHDS[2048], _yHDS[1536];
	int     _xSDS[1024], _ySDS[768];
	int     _xSDW[1366], _ySDW[768];

	int					_iSizeX, _iSizeY;					// aktualne wspolrzedne ekranu
	bool				_isSDS, _isSDW, _isHDS, _isHDW;		// jaki typ rozdzielczosci
	bool				_isHD;								// czy to jest HDS lub HDW

	SDL_DisplayMode		_mode;
	SDL_Window			*_window;
	SDL_GLContext		_gl;

	float				_fPixelRatio, _fReverseRatio;

	unsigned int        _iGridX[101];						// siatka w procentach
    unsigned int        _iGridY[101];

    float	_pixelX, _pixelY;								// rozmiar pixela

};


