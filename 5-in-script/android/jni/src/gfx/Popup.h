
// popup manager
// max 64 popups

#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include "../Main.h"
#include "../GameObject.h"
#include "Sprite.h"
#include "Screen.h"

#define	POPUP_FLASH_BLACK		10
#define	POPUP_FLASH_WHITE		20
#define POPUP_FADE_WHITE		30
#define POPUP_FADE_BLACK		40

#define POPUP_INGAME_START		50
#define POPUP_INGAME_GOOD1		60
#define POPUP_INGAME_GOOD2		70
#define POPUP_INGAME_GOOD3		80
#define POPUP_INGAME_GOOD4		90
#define POPUP_INGAME_GOOD5		100

class CPopup: public CGameObject
{
	public:
		CPopup();
		CPopup(char cFile[]);									// init from .ini
		~CPopup();

		void	Open(CScreen *pScreen);				// load 
		void	Close(void);						// unload 

		void	Add(int iPopupType, unsigned long ulTimer);		// add popup to quene 

		void	Render(unsigned long ulTimer);		// render active popups
		
		bool	isActive(int i);
		void	isActive(int i, bool b);

		void	Stop(void);								// stop all popups
		void	Start(void);							// start all popups

		void	Stop(int i);							// stop selected popup
		void	Start(int i);

	private:

		bool			_bPopupActive[64];			// activity flag 
		int				_iType[64];				// type popup
		unsigned long	_ulTimerStart[64];		// popup start timer 
		
		CSprite		*_pWhiteFlash;			// white screen 
		CSprite		*_pBlackFlash;			// black screen 

		CSprite		*_pStart;
		CSprite		*_pGood1;				// do not look here  ;)
		CSprite		*_pGood2;
		CSprite		*_pGood3;
		CSprite		*_pGood4;
		CSprite		*_pGood5;		

};
