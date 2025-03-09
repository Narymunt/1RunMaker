// 3 state button class 

#pragma once

#include "../Main.h"
#include "Sprite.h"
#include "../control/Touch.h"
#include "../gfx/Screen.h"

#define ON_NONE		0
#define	ON_LEFT		10
#define ON_RIGHT	20
#define	ON_CENTER	30
#define ON_OVER		40

class CButton  
{
public:

	// nazwy plikow i rozdzielczosci zasobow ustalane sa na podstawie parametrow ekranu

	CButton(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[]);
	CButton(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[], int x1, int y1, int x2, int y2);		// wspolrzedne bezwzgledne
	CButton(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[], int x, int y);						// rozmiary przycisku odczytujemy z grafiki

	CButton(CScreen *pScreen, char cName[]);		// wszystkie nazwy wygenerowane _image _over _click

	// nazwy plikow dokladnie takie jak podane w parametrach

	CButton(char cImage[], char cOnOver[], char cOnClick[]);
	CButton(char cImage[], char cOnOver[], char cOnClick[], int x1, int y1, int x2, int y2);						// wspolrzedne bezwzgledne
	CButton(char cImage[], char cOnOver[], char cOnClick[], int x, int y);											// rozmiary przycisku odczytujemy z grafiki

	~CButton();

	void Init(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[], int x1, int y1, int x2, int y2);	// wywolywane z konstruktorow

	int Render(CTouch *pTouch); 		// render button
	int RenderC(CTouch *pTouch);		// render centered button

	void Position(int x, int y);		// wspolrzedne bezwzgledne, zmienia pozycje grafiki ale nie aktywnych wspolrzednych

	// hot coords
	
	void SetHotCoords(int x1, int y1, int x2, int y2);		// zmiana obszaru na wspolrzednych bezwzglednych, nie zmienia rozmiaru grafiki

	void Resize(int x1, int y1, int x2, int y2);			// zmiana rozmiaru grafiki, nie zmienia aktywnych wspolrzednych

private:
	
	int			_x1, _y1, _x2, _y2;

	CSprite		*_pOnClick;
	CSprite		*_pOnOver;
	CSprite		*_pImage;		

};

