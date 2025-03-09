// State - stan aplikacji (aktualnie otwarty ekran/okno)

#pragma once

#include "iGame.h"
#include "State.h"
#include "Screen.h"
#include "Button.h"
#include "Sprite.h"
#include "Mouse.h"

class CIntro : public CState
{

public:

	CIntro(CScreen *pScreen);
	~CIntro();

	void		Open(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CMouse *pMouse);

protected:

	CSprite		*_pBlack;
	CSprite		*_pCompanyLogo;
	CSprite		*_pGameLogo;

};

