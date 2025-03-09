#pragma once

#include <GLES/gl.h>
#include <GLES/glext.h>
#include "SDL.h"
#include "../SDL_image/SDL_image.h"
#include "Screen.h"

class CSprite  
{

public:

	// w tym przypadku nazwa pliku jest bezwzgledna

	CSprite(char cFilename[]);
	CSprite(char cFilename[], int iX, int iY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot);
	CSprite(char cFilename[], int iX, int iY, float fAlfa);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot);
	CSprite(char cFilename[], float fAlfa);

	// w tych konstruktorach generujemy nazwy plikow z uwzglednieniem rozdzielczosci

	CSprite(CScreen *pScreen, char cFilename[]);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY, float fRot);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fAlfa);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot);
	CSprite(CScreen *pScreen, char cFilename[], float fAlfa);

	~CSprite();

	SDL_PixelFormat oglGetPixelFormat(GLenum glFormat);

	void	Init(CScreen *pScreen, char cFilename[]);

	void	Render(int x, int y, float a);
	void	Render(void);						// use top left coords
	void	RenderC(void);						// use texture centre coords

	void	Update(void);						// update factors and render
	void	UpdateC(void);
	
	void	Render(unsigned long ulTimer);		// tutaj wszystkie parapetry sa aktualizowane na podstawie timera

	void	Resize(int x1, int y1, int x2, int y2);		// set size to requested
	void	Scale(float fX, float fY);

	void	Fullscreen(CScreen *pScreen);

	void 	Position(float fX, float fY);

	void 	Color(float r, float g, float b, float a);
	void 	Color(float r, float g, float b);

	bool				_isCenter;					// false = lewy gorny rog, true = srodek tekstury

	float				_fRotation;			
	float				_fSizeX, _fSizeY;			// aktualny rozmiar tekstury liczony w pixelach
	float				_fOriginalX, _fOriginalY;	// pierwotny rozmiar textury
	float				_fScaleX, _fScaleY;
	float				_fPositionX, _fPositionY;
	float				_fAlfa;

	// incrementators, how much do we want to add per rendered frame

	float				_fRotationI;
	float				_fScaleXI, _fScaleYI;
	float				_fPositionXI, _fPositionYI;
	float				_fAlfaI;

	unsigned long		_ulRenderTime;	// czas renderowania ostatniej klatki
	unsigned long		_ulDeltaTime;	// roznica pomiedzy ostatnim renderowaniem a aktualnym timerem
	// our texture
	float				_r, _g, _b, _a;					// kolor naszego sprite
	GLuint				_pSprite;		// identyfikator tekstury

};

 

