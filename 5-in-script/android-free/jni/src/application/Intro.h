// State - stan aplikacji (aktualnie otwarty ekran/okno)

#pragma once

#include "Main.h"
#include "State.h"
#include "../gfx/Screen.h"
#include "../gfx/Button.h"
#include "../gfx/Sprite.h"
#include "../control/Touch.h"

class CIntro : public CState
{

public:

	CIntro(CScreen *pScreen);
	~CIntro();

	void		Open(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CTouch *pTouch);

protected:

	CSprite		*_pBlack;
	CSprite		*_pCompanyLogo;
	CSprite		*_pGameLogo;

};

