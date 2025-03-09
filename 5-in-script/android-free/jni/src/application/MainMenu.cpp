#include "MainMenu.h"

//=== onstruktor

CMainMenu::CMainMenu(CScreen *pScreen) :
_pBackground(0), _pTitle(0),
_pBlack(0), _pWhite(0),
_pFont(0), _pParticleManager(0),
_isFirstRun(true),
_taptapText(0),
_lastClick(0)
{

	CProfile *pProfile;

	_pScreen = pScreen;
	_isActive = false;
	_isMouseLock = true;
	_ulTimerStart = 0;

	// wczytanie odpowiedniego profilu

/*
	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	m_ucCurrentProfile = pProfile->ucCurrentProfile();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(m_pUserName[i],pProfile->pGetName());
	}

	delete pProfile;
*/

	for (int i=0; i<18; i++)
		_cEditName[i] = 0;

}

//=== destructor 

CMainMenu::~CMainMenu()
{
	Close();
}

//=== load and prepare data

int CMainMenu::iOpen(void)
{

	CProfile *pProfile;

	if (_pBackground == NULL)
	{
		_pBackground = new CSprite(_pScreen,(char*)"e_mmenu");
		_pBackground->Fullscreen(_pScreen);

		_pBlack = new CSprite((char*)"black.png");
		_pBlack->Resize(0, 0, _pScreen->_iSizeX, _pScreen->_iSizeY);

		_pWhite = new CSprite((char*)"white.png");
		_pWhite->Fullscreen(_pScreen);

//		_pFont = new CSpriteFont(_pScreen);

		return 20;
	}

	if (_pParticleManager == NULL)
	{
		_pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                               (double)-100,(double)-100,(double)_pScreen->_iSizeX+100,(double)_pScreen->_iSizeY+100,
											   (double)0.01f,(double)0.01f,(double)0.3f,(double)0.3f,
											   (double)0.5f, (double)-.001f,(double).001f,
                                               0.5f, -.5f,.5f,
											   1000,10000);

		_pParticleManager->Color(0.95f, 0.82f, 0.0f, 1.0f);

		_taptapText = new CSprite(_pScreen,(char*)"taptap");

		return 95;
	}

	if (_pTitle == NULL)
	{
		_pScreen->_isHD ?
				_pTitle = new CSprite((char*)"title1024.png") :
				_pTitle = new CSprite((char*)"title512.png");

		_pTitle->Position((_pScreen->_iSizeX/2)-(_pTitle->_fSizeX/2),(_pScreen->_iSizeY/2)-(_pTitle->_fSizeY/2));

		return 100;
	}

/*
	// zaktualizuj informacje o profilu

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	_ucCurrentProfile = pProfile->ucCurrentProfile();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		strcpy(_pUserName[i],pProfile->pGetName());
	}

	delete pProfile;
*/

	_lastClick = 0;
	_isActive = true;
	_isMouseLock = true;
	_ulTimerStart = 0;

	return 101;
}

//=== release data

void CMainMenu::Close(void)
{
/*
	CProfile *pProfile;

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	for (int i=0; i<8; i++)
	{
		pProfile->ucCurrentProfile(i);
		pProfile->SetName(m_pUserName[i]);
	}

	pProfile->ucCurrentProfile(m_ucCurrentProfile);

	pProfile->bSave();

	delete pProfile;
*/

	SafeDelete(_pBackground);
	SafeDelete(_pTitle);

	SafeDelete(_pBlack);
	SafeDelete(_pWhite);

	SafeDelete(_pFont);
	SafeDelete(_pParticleManager);
	SafeDelete(_taptapText);

	_isActive = false;
	_isMouseLock = true;
}


// rysuj ekran

int CMainMenu::iRender(unsigned long ulTimer, CTouch *pTouch)
{

	int iReturn = 0;
	int iDelta;

	if (!_isActive)
		Open();

	if (!pTouch->_isTouch)
		_isMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	iDelta = ulTimer - _ulTimerStart;

	_pBackground->Render();

	_pParticleManager->Render(ulTimer);

	_pTitle->Render();												// logo gry

	if ((ulTimer%1000)<500)
		_taptapText->Render();

	if (pTouch->_isTouch && !_isMouseLock)
	{
		if (ulTimer-_lastClick>10 && ulTimer-_lastClick<2000)
			iReturn = 1;

		_lastClick = ulTimer;
		_isMouseLock = true;
	}


/*
	if (!_isProfileView)			// nie jestesmy w trybie przegladania profili
	{
		_pBackground->Render();

		if (_pButtonStart->Render(pTouch)==ON_LEFT && !_bMouseLock) iReturn = 1;


		_pFont->Print(25,300,1, 0.1f, 0.1f, _pUserName[_ucCurrentProfile]);


	} // if (!_isProfileView)
*/
	return iReturn;

}

