#pragma once

// klawiatura dotykowa na urzadzeniach mobilnych

#include "Sprite.h"
#include "Button.h"
#include "Screen.h"

class CMobileKeyboard
{

public:

	CMobileKeyboard();				// konstruktor czysci zmienne (NULL)
	~CMobileKeyboard();		// destruktor zwalnia pamiec i urzadzenie

	CMobileKeyboard(char cLanguage);				// konstruktor czysci zmienne (NULL)

	void Open(CScreen *pScreen);
	void Close(void);

	unsigned char  cRender(CTouch *pTouch, unsigned long ulTimer);					// zwraca numer nacisnietego przycisku

	CScreen		*_pScreen;
	bool		_isActive;

private :

	char	_cLanguage;

	char	_cState;		// 0 wylaczona i nieaktywna
							// 1 nie aktywna, wysuwa sie
							// 2 aktywna
							// 3 nie aktywna chowa sie

	CSprite	*_pKeyboardBackground;	// podklad pod klawisze

	CButton *_pKeyA;
	CButton *_pKeyB;
	CButton *_pKeyC;
	CButton *_pKeyD;
	CButton *_pKeyE;
	CButton *_pKeyF;
	CButton *_pKeyG;
	CButton *_pKeyH;
	CButton *_pKeyI;
	CButton *_pKeyJ;
	CButton *_pKeyK;
	CButton *_pKeyL;
	CButton *_pKeyM;
	CButton *_pKeyN;
	CButton *_pKeyO;
	CButton *_pKeyP;
	CButton *_pKeyQ;
	CButton *_pKeyR;
	CButton *_pKeyS;
	CButton *_pKeyT;
	CButton *_pKeyU;
	CButton *_pKeyW;
	CButton *_pKeyV;
	CButton *_pKeyX;
	CButton *_pKeyY;
	CButton *_pKeyZ;

	CButton *_pKey0;
	CButton *_pKey1;
	CButton *_pKey2;
	CButton *_pKey3;
	CButton *_pKey4;
	CButton *_pKey5;
	CButton *_pKey6;
	CButton *_pKey7;
	CButton *_pKey8;
	CButton *_pKey9;

	CButton *_pKeySPACE;
	CButton *_pKeyDELETE;
	CButton *_pKeyENTER;
		
	unsigned long _ulTimerOpen;
	unsigned long _ulTimerClose;
	

};

