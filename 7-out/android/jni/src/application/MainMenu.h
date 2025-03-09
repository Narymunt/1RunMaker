// MainMenu - glowne menu gry

#pragma once

#include "Main.h"
#include "State.h"
#include "../gfx/Screen.h"
#include "../gfx/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/SpriteFont.h"
#include "../gfx/Particle2DManager.h"
#include "../gfx/FXManager.h"
#include "../control/Touch.h"
#include "../system/Profile.h"

class CMainMenu : public CState
{

public:

	CMainMenu(CScreen *pScreen);
	~CMainMenu();

	int 		iOpen(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CTouch *pTouch);

protected:

	unsigned long		_lastClick;

	char				_cEditName[18];				// nowa nazwa gracza

	bool				_isFirstRun;				// czy to pierwsze uruchomienie ?

	CSprite				*_pBackground;				// tlo z logiem gry
	CSprite				*_pTitle;					// tytu¸ gry

	CSprite				*_pBlack;					// czarny ekran
	CSprite				*_pWhite;					// bialy ekran

	CSprite				*_taptapText;				// migajacy napis taptap

	CSpriteFont			*_pFont;

	char				_cUserName[8][20];
	unsigned char		_ucCurrentProfile;

	CParticle2DManager	*_pParticleManager;

};

