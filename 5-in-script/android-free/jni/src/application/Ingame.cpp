#include "Ingame.h"

#pragma warning(disable : 4996)	// sprintf unsafe

// class constructor

CIngame::CIngame()
{
	// znaczniki dla kanalow audio sa sciszone

	_iSuperChannel=0;
	_iRainbowChannel=0;
	_iDiamondChannel=0;
	_iLevelUpChannel=0;
	_iClickChannel=0;
	_iBombChannel=0;
	_iTikTakChannel=0;

	_pFXManager = NULL;
	_level = 1;
	_isActive=false;

	m_pBlack = NULL;
	m_pBackground = NULL;
	m_pBoard = NULL;

	for (int i=0; i<GEMS_COUNT; i++)
		m_pGem[i]=NULL;

	for (int i=0; i<10; i++)
		m_pNumber[i]=NULL;

	m_pTimeBar = NULL; 
	m_pExpBar = NULL;
	m_pGreyBar = NULL;

	m_ulTimerStart = 0;	// poczatek
	m_ulPrevTimer = 0;

	m_cClickedA = -1;	// zadne nie klikniete
	m_cClickedB = -1;
	m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 

	m_ulBonusTime = 0;	// dodatek do czasu
	m_ulBonusExp = 0;

	m_bMouseLock = false;
	m_bFallLock = false;

	m_pGameOver = NULL;
	m_bGameOver = false;
	m_lInGameOver = 0;

	m_pParticleManager = NULL;

	m_pHint = NULL;
	m_lHintTime = 0;

	m_iHintX = 0; m_iHintY = 0;

	m_ulScore = 0;

	m_pButtonMenu = NULL;
	m_pButtonHint = NULL;

	m_ucScoreMulti = 0;
	
	for (int i=0; i<=9; i++)
		m_pScoreMulti[i] = NULL;

	m_bHint = false;

	_pScore100 = NULL;
	_pScore250 = NULL;
	_pScore500 = NULL;
	_pScore1000 = NULL;

	m_pPopup = NULL;

	// gems animations

	_pGemRock = NULL;
	_pGemDiamond = NULL;
	_pGemRainbow = NULL;
	_pGemBomb = NULL;

	// audio chunks

	_pMSuper = NULL;
	_pMRainbow = NULL;
	_pMDiamond = NULL;
	_pMLevelUp = NULL;
	_pMClick = NULL;
	_pMBomb = NULL;

	_pGameOverSFX = NULL;
	_pTikTakSFX = NULL;

}

// class destructor

CIngame::~CIngame()
{
	Close();
}

// load data

void CIngame::Open(CScreen *pScreen)
{	
	char cBuffer[16];

	// znaczniki dla kanalow audio sa sciszone

	_iSuperChannel=0;
	_iRainbowChannel=0;
	_iDiamondChannel=0;
	_iLevelUpChannel=0;
	_iClickChannel=0;
	_iBombChannel=0;
	_iTikTakChannel=0;

	_level = 1;

	_iHintID = -1;
	m_bHint = false;

	m_ulScore = 0;			// iloœæ punktów
	m_ucScoreMulti = (unsigned char) _level -1;		// jaki mno¿nik

	m_ulTimer1000 = 0;		// czas 10 sek temu
	m_ulScore1000 = 0;		// punkty 10 sek temu
	m_ulTimerStart = 0;	// poczatek

	m_pBlack = new CSprite((char*)"black.png");
	m_pBlack->Fullscreen(pScreen);

	m_pBackground = new CSprite(pScreen,(char*)"background");
	m_pBackground->Fullscreen(pScreen);

	m_pGameOver = new CSprite(pScreen,(char*)"gameover");
	m_pGameOver->Fullscreen(pScreen);

	m_pParticleManager = new CParticle2DManager((char*)"k3.png", 150,
		-100, -100, pScreen->_iSizeX+100, pScreen->_iSizeY+100,
		0.01f, 0.01f, 0.3f, 0.3f,
		0.5f, -.001f, .001f,
		0.5f, -1.0f, 1.0f,
		1000, 10000);

	_pFXManager = new CFXManager();

	// popup manager

	m_pPopup = new CPopup();
	m_pPopup->Open(pScreen);

	// liczniki, timery i inne bajery

	m_ulTimerStart = 0;	// poczatek
	m_ulPrevTimer = 0;

	m_cClickedA = -1;	// zadne nie klikniete
	m_cClickedB = -1;
	m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1;

	m_ulBonusTime = 0;	// dodatek do czasu
	m_ulBonusExp = 0;

	m_bMouseLock = false;
	m_bFallLock = false;

	m_bGameOver = false;
	m_lInGameOver = 0;

	m_iHintX = 0;
	m_iHintY = 0;

	_uiMatchCount = 0;

	m_bHint = false;

	_pScreen = pScreen;

	m_lHintTime = 0;

	for (int i=0; i<64; i++)
	{
		m_cBoard[i]= 0;
		m_bBoard[i]= true;
		m_fBoardDeltaX[i] = 0.0f;
		m_fBoardDeltaY[i] = 0.0f;

		m_cScaleBoard[i]=-1;
		m_fScaleBoard[i]= 1.0f;
		m_ulScaleTimer[i]= 0;
	}

	_isGameOverSFX = false;	// jeszcze nie odtworzylismy dzwieku game over
	_isTikTakSFX = false;	// nie odtwarzamy tiktak

	// offset dla tablicy

	if (pScreen->_isSDS)
	{
		_uiBoardOffsetY = 64;
	}
	else if (pScreen->_isSDW)
	{
		_uiBoardOffsetY = 64;
	}
	else if (pScreen->_isHDW)
	{
		_uiBoardOffsetY = 64;
	}
	else if (pScreen->_isHDS)
	{
		_uiBoardOffsetY = 64;
	}

	M3_DELTA = 16.0f;

	if (_pScreen->_iSizeX < 1500)
	{
		_ucGemSize = 64;
		_ucGemSizeHalf = 32;
	}
	else if (_pScreen->_isHDW)
	{
		_ucGemSize = 96;
		_ucGemSizeHalf = 48;
	}
	else if (_pScreen->_isHDS)
	{
		_ucGemSize = 128;
		_ucGemSizeHalf = 64;
	}

	for (int i=0; i<64; i++)
	{
		m_iCoin[i] = -1;
		_sCoin[i] = 0;
	}

	// init all audio chunks

	_pMSuper = Mix_LoadWAV("super.ogg");
	_pMRainbow = Mix_LoadWAV("rainbow.ogg");
	_pMDiamond = Mix_LoadWAV("diamond.ogg");
	_pMLevelUp = Mix_LoadWAV("level_up.ogg");
	_pMClick = Mix_LoadWAV("click.ogg");
	_pMBomb = Mix_LoadWAV("bomb.ogg");
	_pGameOverSFX = Mix_LoadWAV("gameover.ogg");
	_pTikTakSFX = Mix_LoadWAV("tiktak.ogg");

	if (pScreen->_isHD)
	{
		pScreen->_isHDS ? m_pBoard = new CSprite((char*)"board1024.png") : m_pBoard = new CSprite((char*)"board768.png");
		m_pBoard->Position(pScreen->_iSizeX/2,(m_pBoard->_fSizeY/2)+_uiBoardOffsetY);
	}
	else
	{
		m_pBoard = new CSprite((char*)"board512.png");
		m_pBoard->Position(pScreen->_iSizeX/2,64+256);
	}

	m_pTimeBar = new CSprite((char*)"bar_red.png");
	m_pExpBar =  new CSprite((char*)"bar_green.png");
	m_pGreyBar = new CSprite((char*)"bar_grey.png");

	m_pHint = new CSprite(pScreen,"hint");

	// ikony x1,x2 itd. 

	for (int i=0; i<=9; i++)
	{
		sprintf(cBuffer,"x%d",i+1);
		m_pScoreMulti[i] = new CSprite(pScreen,cBuffer);
	}
	
	// obrazki kamykow

	for (int i=0; i<=GEMS_COUNT-1; i++)
	{
		if (pScreen->_isHDS)
		{
			sprintf(cBuffer,"gem%db.png",i+1);
		}
		else if (pScreen->_isHDW)
		{
			sprintf(cBuffer,"gem%dc.png",i+1);
		}
		else
		{
			sprintf(cBuffer,"gem%d.png",i+1);
		}
			m_pGem[i] = new CSprite(cBuffer);
	}

	// animacje dla specjalnych klockow

	if (pScreen->_isHDS)
	{
		_pGemRock = new CAnimation((char*)"gem8b_",1,(char*)"png");
		_pGemDiamond = new CAnimation((char*)"gem9b_",1,(char*)"png");
		_pGemRainbow = new CAnimation((char*)"gem10b_",1,(char*)"png");
		_pGemBomb = new CAnimation((char*)"gem11b_",1,(char*)"png");
	}
	else if (pScreen->_isHDW)
	{
		_pGemRock = new CAnimation((char*)"gem8c_",1,(char*)"png");
		_pGemDiamond = new CAnimation((char*)"gem9c_",1,(char*)"png");
		_pGemRainbow = new CAnimation((char*)"gem10c_",1,(char*)"png");
		_pGemBomb = new CAnimation((char*)"gem11c_",1,(char*)"png");
	}
	else
	{
		_pGemRock = new CAnimation((char*)"gem8_",1,(char*)"png");
		_pGemDiamond = new CAnimation((char*)"gem9_",1,(char*)"png");
		_pGemRainbow = new CAnimation((char*)"gem10_",1,(char*)"png");
		_pGemBomb = new CAnimation((char*)"gem11_",1,(char*)"png");
	}

	_pGemRock->Open();
	_pGemDiamond->Open();
	_pGemRainbow->Open();
	_pGemBomb->Open();

	// przyciski podpowiedzi i wyjscia do menu

	 if (pScreen->_isHDS)
	 {
		 m_pButtonHint = new CButton((char*)"hint_click_256px.png",(char*)"hint_over_256px.png",(char*)"hint_static_256px.png",0,0,256,256);
	     m_pButtonHint->Position(pScreen->x(1600),pScreen->y(1170));
	     m_pButtonHint->SetHotCoords(pScreen->x(1600),pScreen->y(1170),pScreen->x(1600)+256,pScreen->y(1170)+256);

	     m_pButtonMenu = new CButton((char*)"menu_click_256px.png",(char*)"menu_over_256px.png",(char*)"menu_static_256px.png",0,0,256,256);
	     m_pButtonMenu->Position(pScreen->x(170),pScreen->y(1170));
	     m_pButtonMenu->SetHotCoords(pScreen->x(170),pScreen->y(1170),pScreen->x(170)+256,pScreen->y(1170)+256);
	 }
	 else if (pScreen->_isSDS)
	 {
		 m_pButtonHint = new CButton((char*)"hint_click_128px.png",(char*)"hint_over_128px.png",(char*)"hint_static_128px.png",0,0,128,128);
	     m_pButtonHint->Position(pScreen->x(800),pScreen->y(600));
	     m_pButtonHint->SetHotCoords(pScreen->x(800),pScreen->y(600),pScreen->x(800)+128,pScreen->y(600)+128);

	     m_pButtonMenu = new CButton((char*)"menu_click_128px.png",(char*)"menu_over_128px.png",(char*)"menu_static_128px.png",0,0,128,128);
	     m_pButtonMenu->Position(pScreen->x(80),pScreen->y(600));
	     m_pButtonMenu->SetHotCoords(pScreen->x(80),pScreen->y(600),pScreen->x(80)+128,pScreen->y(600)+128);
	 }
	 else if (pScreen->_isSDW)
	 {
	     m_pButtonHint = new CButton((char*)"hint_click_128px.png",(char*)"hint_over_128px.png",(char*)"hint_static_128px.png",0,0,128,128);
	     m_pButtonHint->Position(pScreen->x(950),pScreen->y(575));
	     m_pButtonHint->SetHotCoords(pScreen->x(950),pScreen->y(575),pScreen->x(950)+128,pScreen->y(575)+128);

	     m_pButtonMenu = new CButton((char*)"menu_click_128px.png",(char*)"menu_over_128px.png",(char*)"menu_static_128px.png",0,0,128,128);
	     m_pButtonMenu->Position(pScreen->x(260),pScreen->y(575));
	     m_pButtonMenu->SetHotCoords(pScreen->x(260),pScreen->y(575),pScreen->x(260)+128,pScreen->y(575)+128);
	 }
	 else if (pScreen->_isHDW)
	 {
		 m_pButtonHint = new CButton((char*)"hint_click_256px.png",(char*)"hint_over_256px.png",(char*)"hint_static_256px.png",0,0,256,256);
	     m_pButtonHint->Position(pScreen->x(1302),pScreen->y(800));
	     m_pButtonHint->SetHotCoords(pScreen->x(1302),pScreen->y(800),pScreen->x(1302)+256,pScreen->y(800)+256);

	     m_pButtonMenu = new CButton((char*)"menu_click_256px.png",(char*)"menu_over_256px.png",(char*)"menu_static_256px.png",0,0,256,256);
	     m_pButtonMenu->Position(pScreen->x(300),pScreen->y(800));
	     m_pButtonMenu->SetHotCoords(pScreen->x(300),pScreen->y(800),pScreen->x(300)+256,pScreen->y(800)+256);
	 }

	 // numer

 	 for (int i=0; i<=9; i++)
 	 {
 		 pScreen->_isHD ? sprintf(cBuffer,"%db.png",i) : sprintf(cBuffer,"%d.png",i); // @suppress("Function cannot be resolved")
 		 m_pNumber[i] = new CSprite(cBuffer);
 	 }

	// punkty nad klockami

	_pScore100 = new CSprite(pScreen,(char*)"score100");
	_pScore250 = new CSprite(pScreen,(char*)"score250");
	_pScore500 = new CSprite(pScreen,(char*)"score500");
	_pScore1000 = new CSprite(pScreen,(char*)"score1000");

	_isActive = true;	// data loaded

}

// free graphics and music, but keep the required data

void CIngame::Close(void)
{
	SafeDelete(_pFXManager);

	SafeDelete(m_pBoard);
	SafeDelete(m_pBlack);
	SafeDelete(m_pBackground);
	
	SafeDelete(m_pTimeBar);
	SafeDelete(m_pExpBar);
	SafeDelete(m_pGreyBar);
	SafeDelete(m_pGameOver);

	for (int i=0; i<=GEMS_COUNT; i++)
		SafeDelete(m_pGem[i]);

	SafeDelete(_pGemRock);
	SafeDelete(_pGemDiamond);
	SafeDelete(_pGemRainbow);
	SafeDelete(_pGemBomb);

	for (int i=0; i<10; i++)
		SafeDelete(m_pNumber[i]);

	SafeDelete(m_pParticleManager);
	SafeDelete(m_pButtonMenu);
	SafeDelete(m_pButtonHint);

	for (int i=0; i<=9; i++)
		SafeDelete(m_pScoreMulti[i]);

	SafeDelete(m_pPopup);
	SafeDelete(m_pHint);

	SafeDelete(_pScore100);
	SafeDelete(_pScore250);
	SafeDelete(_pScore500);
	SafeDelete(_pScore1000);

	// release audio chunks

	if (_pMSuper!=NULL)
	{
		Mix_FreeChunk(_pMSuper);
		_pMSuper = NULL;
	}

	if (_pMRainbow!=NULL)
	{
		Mix_FreeChunk(_pMRainbow);
		_pMRainbow = NULL;
	}

	if (_pMDiamond!=NULL)
	{
		Mix_FreeChunk(_pMDiamond);
		_pMDiamond = NULL;
	}

	if (_pMLevelUp!=NULL)
	{
		Mix_FreeChunk(_pMLevelUp);
		_pMLevelUp = NULL;
	}

	if (_pMClick!=NULL)
	{
		Mix_FreeChunk(_pMClick);
		_pMClick = NULL;
	}
	
	if (_pMBomb!=NULL)
	{
		Mix_FreeChunk(_pMBomb);
		_pMBomb = NULL;
	}

	if (_pGameOverSFX != NULL)
	{
		Mix_FreeChunk(_pGameOverSFX);
		_pGameOverSFX = NULL;
	}

	if (_pTikTakSFX != NULL)
	{
		Mix_FreeChunk(_pTikTakSFX);
		_pTikTakSFX = NULL;
	}

	m_ulTimerStart = 0;	// poczatek

	m_bHint = false;

	_isActive = false;
}

// add points

void CIngame::Advance(unsigned long ulBonusTime, unsigned long ulBonusExp, unsigned long ulScore)
{
	m_ulBonusTime += ulBonusTime;
	m_ulBonusExp += ulBonusExp;
	m_ulScore += ulScore;

	_uiMatchCount++;	// licznik ulozonych kombinacji, zeby mozna bylo sprawdzic czy mozemy dodac archievement
}

// update board when correct combination found

//=== sprawdzamy czy na planszy jest wlasciwa kombinacja, jesli tak to przestawiamy klocki

bool CIngame::isMatch3(unsigned long ulTimer)
{
	bool bFound;
	int h1,h2, adres;

	bFound = false;

	// szukamy L, 3 kamykow w pionie i poziomie aby utworzyc diament

	// +-	szukamy lewego gornego rogu
	// |

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && 
				m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[adres+1] == 0 && m_fBoardDeltaY[adres+1] == 0 &&
				m_fBoardDeltaX[adres+2] == 0 && m_fBoardDeltaY[adres+2] == 0 &&
				m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
				!m_bBoard[((h1+1)*8)+h2+1] &&		// sprawdzamy czy pod spodem nie ma wolnych miejsc
				!m_bBoard[((h1+1)*8)+h2+2] &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[adres] = GEM_DIAMOND;
				_iDiamondChannel = Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[adres] = ulTimer;	// dodajemy monetê
				_sCoin[adres] = 500;		// dajemy +250
				Advance(0,50,500);

				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[adres+1] = m_cBoard[adres+1];
				m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
				m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];

				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;

				m_cBoard[adres+1] = -1;
				m_bBoard[adres+1] = true;

				m_cBoard[adres+2] = -1;
				m_bBoard[adres+2] = true;

				m_cBoard[((h1+1)*8)+h2] = -1;
				m_bBoard[((h1+1)*8)+h2] = true;

				m_cBoard[((h1+2)*8)+h2] = -1;
				m_bBoard[((h1+2)*8)+h2] = true;

				// dodajemy czas, doœwiadczenie, punkty
				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);

				bFound = true;
			}
		}
	}

	// -+	szukamy prawego gornego rogu
	//  |

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && 
				m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2+2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2+2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[adres+1] == 0 && m_fBoardDeltaY[adres+1] == 0 &&
				m_fBoardDeltaX[adres+2] == 0 && m_fBoardDeltaY[adres+2] == 0 &&
				m_fBoardDeltaX[((h1+1)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2+2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2+2] == 0 &&
				!m_bBoard[((h1+1)*8)+h2-1] &&		// sprawdzamy czy pod spodem nie ma wolnych miejsc
				!m_bBoard[((h1+1)*8)+h2-2] &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[adres+2] = GEM_DIAMOND;
				_iDiamondChannel = Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
				_sCoin[adres+2] = 500;		// dajemy +250
				Advance(0,50,500);

				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[adres+1] = m_cBoard[adres+1];
				m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
				m_cScaleBoard[((h1+1)*8)+h2+2] = m_cBoard[((h1+1)*8)+h2+2];
				m_cScaleBoard[((h1+2)*8)+h2+2] = m_cBoard[((h1+2)*8)+h2+2];

				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+1)*8)+h2+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2+2] = (unsigned long)ulTimer;

				m_cBoard[adres] = -1;
				m_bBoard[adres] = true;

				m_cBoard[adres+1] = -1;
				m_bBoard[adres+1] = true;

				m_cBoard[((h1+1)*8)+h2+2] = -1;
				m_bBoard[((h1+1)*8)+h2+2] = true;

				m_cBoard[((h1+2)*8)+h2+2] = -1;
				m_bBoard[((h1+2)*8)+h2+2] = true;

				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	// |	szukamy lewego dolnego rogu
	// +- 

	for (h1=0; h1<=5; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && 
				m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2+1] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2+2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2+1] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2+1] == 0 &&
				m_fBoardDeltaX[((h1+2)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2+2] == 0 &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[((h1+2)*8)+h2] = GEM_DIAMOND;
				_iDiamondChannel = Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê
				_sCoin[((h1+2)*8)+h2] = 500;		// dajemy +250
				Advance(0,50,500);

				m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];
				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];						
				m_cScaleBoard[((h1+2)*8)+h2+1] = m_cBoard[((h1+2)*8)+h2+1];
				m_cScaleBoard[((h1+2)*8)+h2+2] = m_cBoard[((h1+2)*8)+h2+2];

				m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1+2)*8)+h2+2] = (unsigned long)ulTimer;

				m_cBoard[adres] = -1;
				m_bBoard[adres] = true;

				m_cBoard[((h1+1)*8)+h2] = -1;
				m_bBoard[((h1+1)*8)+h2] = true;

				m_cBoard[((h1+2)*8)+h2+1] = -1;
				m_bBoard[((h1+2)*8)+h2+1] = true;

				m_cBoard[((h1+2)*8)+h2+2] = -1;
				m_bBoard[((h1+2)*8)+h2+2] = true;

				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	//  |	szukamy prawego dolnego rogu
	// -+

	for (h1=2; h1<=7; h1++)
	{
		for (h2=0; h2<=5; h2++)
		{
			adres = (h1*8)+h2;

			if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && 
				m_cBoard[adres] == m_cBoard[((h1-1)*8)+h2+2] && m_cBoard[adres] == m_cBoard[((h1-2)*8)+h2+2] &&
				m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
				m_fBoardDeltaX[adres+1] == 0 && m_fBoardDeltaY[adres+1] == 0 &&
				m_fBoardDeltaX[adres+2] == 0 && m_fBoardDeltaY[adres+2] == 0 &&
				m_fBoardDeltaX[((h1-1)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1-1)*8)+h2+2] == 0 &&
				m_fBoardDeltaX[((h1-2)*8)+h2+2] == 0 && m_fBoardDeltaY[((h1-2)*8)+h2+2] == 0 &&
				!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
				m_cBoard[adres]<GEM_ROCK)
			{

				m_cBoard[adres+2] = GEM_DIAMOND;
				_iDiamondChannel = Mix_PlayChannel(-1, _pMDiamond,0);

				m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
				_sCoin[adres+2] = 500;		// dajemy +250
				Advance(0,50,500);

				m_cScaleBoard[adres+2] = m_cBoard[adres+2];
				m_cScaleBoard[adres] = m_cBoard[adres];
				m_cScaleBoard[adres+1] = m_cBoard[adres+1];						
				m_cScaleBoard[((h1-1)*8)+h2+2] = m_cBoard[((h1-1)*8)+h2+2];
				m_cScaleBoard[((h1-2)*8)+h2+2] = m_cBoard[((h1-2)*8)+h2+2];

				m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres] = (unsigned long)ulTimer;
				m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1-1)*8)+h2+2] = (unsigned long)ulTimer;
				m_ulScaleTimer[((h1-2)*8)+h2+2] = (unsigned long)ulTimer;

				m_cBoard[adres+1] = -1;
				m_bBoard[adres+1] = true;

				m_cBoard[adres] = -1;
				m_bBoard[adres] = true;

				m_cBoard[((h1-1)*8)+h2+2] = -1;
				m_bBoard[((h1-1)*8)+h2+2] = true;

				m_cBoard[((h1-2)*8)+h2+2] = -1;
				m_bBoard[((h1-2)*8)+h2+2] = true;

				Advance ((10/(m_ucScoreMulti+1))*3,(100/(m_ucScoreMulti+1))*3,((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10))*3);
						
				bFound = true;
			}
		}
	}

	//=== szukamy 5 kamykow w jednej linii poziomo

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=3; h2++)
			{
			adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && m_cBoard[adres] == m_cBoard[adres+3] && m_cBoard[adres] == m_cBoard[adres+4] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres]==0 && m_fBoardDeltaY[adres]==0 &&	
					m_fBoardDeltaX[adres+1]==0 && m_fBoardDeltaY[adres+1]==0 &&
					m_fBoardDeltaX[adres+2]==0 && m_fBoardDeltaY[adres+2]==0 &&
					m_fBoardDeltaX[adres+3]==0 && m_fBoardDeltaY[adres+3]==0 &&
					m_fBoardDeltaX[adres+4]==0 && m_fBoardDeltaY[adres+3]==0 ) 	// sprawdzamy tylko klocki ktore juz nie sa w ruchu

				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
						{
							m_bBoard[adres] = true;
							m_bBoard[adres+1] = true;
					
							m_cBoard[adres+2] = GEM_RAINBOW;
							m_bBoard[adres+2] = false;
							m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
							_sCoin[adres+2] = 1000;		// dajemy +250
							Advance(0,100,1000);

							m_bBoard[adres+3] = true;
							m_bBoard[adres+4] = true;

							m_cScaleBoard[adres] = m_cBoard[adres];
							m_cScaleBoard[adres+1] = m_cBoard[adres+1];
							m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
							m_cScaleBoard[adres+3] = m_cBoard[adres+3];
							m_cScaleBoard[adres+4] = m_cBoard[adres+4];

							m_ulScaleTimer[adres] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+4] = (unsigned long)ulTimer;

							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
							_iRainbowChannel = Mix_PlayChannel(-1, _pMRainbow,0);
							bFound = true;
						}
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2] && !m_bBoard[((h1+1)*8)+h2+3] && !m_bBoard[((h1+1)*8)+h2+4])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;

								m_cBoard[adres+2] = GEM_RAINBOW;
								m_bBoard[adres+2] = false;
								m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
								_sCoin[adres+2] = 1000;		// dajemy +250
								Advance(0,100,1000);

								m_bBoard[adres+3] = true;
								m_bBoard[adres+4] = true;

								m_cScaleBoard[adres] = m_cBoard[adres];
								m_cScaleBoard[adres+1] = m_cBoard[adres+1];
								m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
								m_cScaleBoard[adres+3] = m_cBoard[adres+3];
								m_cScaleBoard[adres+4] = m_cBoard[adres+4];

								m_ulScaleTimer[adres] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+4] = (unsigned long)ulTimer;

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
								_iRainbowChannel = Mix_PlayChannel(-1, _pMRainbow,0);
								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=3; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+3)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+4)*8)+h2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
					m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+3)*8)+h2] == 0 && m_fBoardDeltaY[((h1+3)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+4)*8)+h2] == 0 && m_fBoardDeltaY[((h1+4)*8)+h2] == 0 )
				{
					if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
					{
						m_bBoard[adres] = true;
						m_bBoard[((h1+1)*8)+h2] = true;
						
						m_cBoard[((h1+2)*8)+h2] = GEM_RAINBOW;
						m_bBoard[((h1+2)*8)+h2] = false;
						m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+2)*8)+h2] = 1000;		// dajemy +250
						Advance(0,100,1000);

						m_bBoard[((h1+3)*8)+h2] = true;
						m_bBoard[((h1+4)*8)+h2] = true;

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];						
						m_cScaleBoard[((h1+3)*8)+h2] = m_cBoard[((h1+3)*8)+h2];
						m_cScaleBoard[((h1+4)*8)+h2] = m_cBoard[((h1+4)*8)+h2];

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+3)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+4)*8)+h2] = (unsigned long)ulTimer;

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						_iRainbowChannel = Mix_PlayChannel(-1, _pMRainbow,0);
						bFound = true;
					}
				}
			}
		}

	// szukamy 4 kamyczków w jednej linii

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=4; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] && m_cBoard[adres] == m_cBoard[adres+3] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres]==0 && m_fBoardDeltaY[adres]==0 &&	
					m_fBoardDeltaX[adres+1]==0 && m_fBoardDeltaY[adres+1]==0 &&
					m_fBoardDeltaX[adres+2]==0 && m_fBoardDeltaY[adres+2]==0 &&
					m_fBoardDeltaX[adres+3]==0 && m_fBoardDeltaY[adres+3]==0)	// sprawdzamy tylko klocki ktore juz nie sa w ruchu

				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
						{
							m_bBoard[adres] = true;
							m_bBoard[adres+1] = true;
							m_bBoard[adres+2] = true;
							m_bBoard[adres+3] = true;

							m_iCoin[adres] = ulTimer;	// dodajemy monetê
							_sCoin[adres] = 100;		// dajemy +250
							m_iCoin[adres+1] = ulTimer;	// dodajemy monetê
							_sCoin[adres+1] = 100;		// dajemy +250
							m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
							_sCoin[adres+2] = 100;		// dajemy +250
							m_iCoin[adres+3] = ulTimer;	// dodajemy monetê
							_sCoin[adres+3] = 100;		// dajemy +250

							Advance(0,40,400);

							m_cScaleBoard[adres] = m_cBoard[adres];
							m_cScaleBoard[adres+1] = m_cBoard[adres+1];
							m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
							m_cScaleBoard[adres+3] = m_cBoard[adres+3];

							m_ulScaleTimer[adres] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;
							
							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2] && !m_bBoard[((h1+1)*8)+h2+3])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;
								m_bBoard[adres+2] = true;
								m_bBoard[adres+3] = true;

								m_iCoin[adres] = ulTimer;	// dodajemy monetê
								_sCoin[adres] = 100;		// dajemy +250
								m_iCoin[adres+1] = ulTimer;	// dodajemy monetê
								_sCoin[adres+1] = 100;		// dajemy +250
								m_iCoin[adres+2] = ulTimer;	// dodajemy monetê
								_sCoin[adres+2] = 100;		// dajemy +250
								m_iCoin[adres+3] = ulTimer;	// dodajemy monetê
								_sCoin[adres+3] = 100;		// dajemy +250

								Advance(0,40,400);

								m_cScaleBoard[adres] = m_cBoard[adres];
								m_cScaleBoard[adres+1] = m_cBoard[adres+1];
								m_cScaleBoard[adres+2] = m_cBoard[adres+2];						
								m_cScaleBoard[adres+3] = m_cBoard[adres+3];

								m_ulScaleTimer[adres] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+3] = (unsigned long)ulTimer;

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=4; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+3)*8)+h2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc	
					m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
					m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+3)*8)+h2] == 0 && m_fBoardDeltaY[((h1+3)*8)+h2] == 0)
				{
					if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
					{
						m_bBoard[adres] = true;
						m_bBoard[((h1+1)*8)+h2] = true;
						m_bBoard[((h1+2)*8)+h2] = true;
						m_bBoard[((h1+3)*8)+h2] = true;

						m_iCoin[adres] = ulTimer;	// dodajemy monetê
						_sCoin[adres] = 100;		// dajemy +250
						m_iCoin[((h1+1)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+1)*8)+h2] = 100;		// dajemy +250
						m_iCoin[((h1+2)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+2)*8)+h2] = 100;		// dajemy +250
						m_iCoin[((h1+3)*8)+h2] = ulTimer;	// dodajemy monetê
						_sCoin[((h1+3)*8)+h2] = 100;		// dajemy +250

						Advance(0,40,400);

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+2)*8)+h2];						
						m_cScaleBoard[((h1+3)*8)+h2] = m_cBoard[((h1+3)*8)+h2];

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+3)*8)+h2] = (unsigned long)ulTimer;

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}


	//=== standardowe sprawdzenie, szukamy 3-jek

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=5; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc
					m_fBoardDeltaX[adres]==0 && m_fBoardDeltaY[adres]==0 &&	
					m_fBoardDeltaX[adres+1]==0 && m_fBoardDeltaY[adres+1]==0 &&
					m_fBoardDeltaX[adres+2]==0 && m_fBoardDeltaY[adres+2]==0 )	// sprawdzamy tylko klocki ktore juz nie sa w ruchu

				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
						{
							m_bBoard[adres] = true;
							m_bBoard[adres+1] = true;
							m_bBoard[adres+2] = true;

							m_cScaleBoard[adres] = m_cBoard[adres];
							m_cScaleBoard[adres+1] = m_cBoard[adres+1];
							m_cScaleBoard[adres+2] = m_cBoard[adres+2];						

							m_ulScaleTimer[adres] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
							m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;

							m_iCoin[adres+1] = ulTimer;	// uruchom animacje tutaj 
							_sCoin[adres+1] = 100;
							Advance(0,10,100);

							Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
						
							bFound = true;
						}
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							{
								m_bBoard[adres] = true;
								m_bBoard[adres+1] = true;
								m_bBoard[adres+2] = true;

								m_cScaleBoard[adres] = m_cBoard[adres];
								m_cScaleBoard[adres+1] = m_cBoard[adres+1];
								m_cScaleBoard[adres+2] = m_cBoard[adres+2];						

								m_ulScaleTimer[adres] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+1] = (unsigned long)ulTimer;
								m_ulScaleTimer[adres+2] = (unsigned long)ulTimer;

								m_iCoin[adres+1] = ulTimer;	// uruchom animacje tutaj 
								_sCoin[adres+1] = 100;
								Advance(0,10,100);

								Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));

								bFound = true;
							}
						}
					}
				}
			}
		}

		for (h1=0; h1<=5; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{

				adres = (h1*8)+h2;
				
				if (m_cBoard[adres] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[adres] == m_cBoard[((h1+2)*8)+h2] &&
					!m_bBoard[adres] &&				// czy my nie sprawdzamy pustych miejsc	
					m_fBoardDeltaX[adres] == 0 && m_fBoardDeltaY[adres] == 0 &&
					m_fBoardDeltaX[((h1+1)*8)+h2] == 0 && m_fBoardDeltaY[((h1+1)*8)+h2] == 0 &&
					m_fBoardDeltaX[((h1+2)*8)+h2] == 0 && m_fBoardDeltaY[((h1+2)*8)+h2] == 0)
				{
					if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
					{
						m_bBoard[adres] = true;
						m_bBoard[((h1+1)*8)+h2] = true;
						m_bBoard[((h1+2)*8)+h2] = true;

						m_cScaleBoard[adres] = m_cBoard[adres];
						m_cScaleBoard[((h1+1)*8)+h2] = m_cBoard[((h1+1)*8)+h2];
						m_cScaleBoard[((h1+2)*8)+h2] = m_cBoard[((h1+1)*8)+h2];						

						m_ulScaleTimer[adres] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+1)*8)+h2] = (unsigned long)ulTimer;
						m_ulScaleTimer[((h1+2)*8)+h2] = (unsigned long)ulTimer;

						m_iCoin[((h1+1)*8)+h2] = ulTimer;	// uruchom animacje tutaj 
						_sCoin[((h1+1)*8)+h2] = 100;
						Advance(0,10,100);

						Advance ((10/(m_ucScoreMulti+1)),(100/(m_ucScoreMulti+1)),((3*(m_ucScoreMulti+1))+(m_ulBonusTime/10)));
	
						bFound = true;
					}
				}
			}
		}

	if (bFound)
		_iClickChannel = Mix_PlayChannel(-1, _pMClick,0);

	return bFound; //false;
}

//=== sprawdzamy czy istnieje kombinacja, ale nie przestawiamy klockow
//=== u¿ywane do podpowiedzi i sprawdzenia czy musimy wylosowaæ na nowo klocki

bool CIngame::isMatch3Check(void)
{
	bool bFound;
	int h1,h2, adres;

	bFound = false;

		for (h1=0; h1<=7; h1++)	// sprawdzamy poziomo
		{
			for (h2=0; h2<=5; h2++)
			{
				adres = (h1*8)+h2;

				if (m_cBoard[adres] == m_cBoard[adres+1] && m_cBoard[adres] == m_cBoard[adres+2])
				{
					if (h1==7)	// w ostatniej lini nie sprawdzamy czy pod klockami jest spacja
					{	
						if (m_cBoard[adres]<GEM_ROCK)		// tylko kamyki standardowe
							bFound = true;
					}
					else
					{
						if (!m_bBoard[((h1+1)*8)+h2] && !m_bBoard[((h1+1)*8)+h2+1] && !m_bBoard[((h1+1)*8)+h2+2])	// czy pod klockami jest spacja ?
						{
							if (m_cBoard[(h1*8)+h2]<GEM_ROCK)		// tylko kamyki standardowe
								bFound = true;
						}
					}
				}
			}
		}

		for (h1=0; h1<=5; h1++)	// sprawdzamy pionowo
		{
			for (h2=0; h2<=7; h2++)
			{
				if (m_cBoard[(h1*8)+h2] == m_cBoard[((h1+1)*8)+h2] && m_cBoard[(h1*8)+h2] == m_cBoard[((h1+2)*8)+h2])
				{
					if (m_cBoard[(h1*8)+h2]<GEM_ROCK)		// tylko kamyki standardowe
						bFound = true;
				}
			}
		}

	return bFound;//false;
}

//=== aktualizacja wspolrzednych klockow
//=== TODO: delta przesuniêcia klocków powinna byæ liczona z timera

bool CIngame::isMoveGems(unsigned long ulTimer)
{
	bool bFallLock = false;

	for (int i=0; i<64;i++)
	{
		if (m_fBoardDeltaX[i]<0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaX[i]+=M3_DELTA;
			
			bFallLock = true;
		}

		if (m_fBoardDeltaX[i]>0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaX[i]-=M3_DELTA;
			
			bFallLock = true;
		}

		if (m_fBoardDeltaY[i]<0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaY[i]+=M3_DELTA;
			
			bFallLock = true;
		}

		if (m_fBoardDeltaY[i]>0)
		{
			if (m_ulPrevTimer != ulTimer)
				m_fBoardDeltaY[i]-=M3_DELTA;
			
			bFallLock = true;
		}
	}

	return bFallLock;

}


// zwraca liczbe przy konwersji znaku z tablicy
// convert char digit to int and return as char :)

char CIngame::cToDigit(char cDigit)
{
	return char((int)cDigit-'0');
}

//=== rysowanie pasków postêpu i pasku czasu

void CIngame::DrawProgressBar(unsigned long ulTimer)
{
	float	fTimeBar, fCurrent;
	int		iTimeX1, iTimeY1, iTimeX2, iTimeY2;
	int		iExpX1, iExpY1, iExpX2, iExpY2;	// wspolrzedne progress barow

	// rysujemy progress bar

	fTimeBar = (float)((ulTimer-m_ulTimerStart)/10)-m_ulBonusTime;

	// jezeli czasu jest za duzo (czyli ponizej 0) to ustawiamy na 0

	if (fTimeBar<0)
		fTimeBar = 0;

	// sprawdzamy czy powinnismy puszczac dzwiek odliczania do konca czasu

	if (fTimeBar > 700)
	{
		if (!_isTikTakSFX)
		{
			_iTikTakChannel = Mix_PlayChannel(-1, _pTikTakSFX, -1);
			_isTikTakSFX = true;
		}
	}
	else
	{
		if (_isTikTakSFX)
		{
			Mix_HaltChannel(_iTikTakChannel);
			_isTikTakSFX = false;
		}
	}


	// jezeli czasu jest za malo, progress bar jest ponizej 0, to dajemy game over

	if (fTimeBar>1000)
	{
		fTimeBar = 0.0f;
		m_bGameOver = true;
		m_ulTimerStart = 0;
		m_ulPrevTimer = 0;
	}

	// ustawianie wspolrzednych

	if (_pScreen->_isSDS)
	{
		iTimeX1 = _pScreen->x(334); iTimeY1 = _pScreen->y(632);
		iTimeX2 = _pScreen->x(700); iTimeY2 = _pScreen->y(664);

		iExpX1 = _pScreen->x(334); iExpY1 = _pScreen->y(680);
		iExpX2 = _pScreen->x(700); iExpY2 = _pScreen->y(712);
	}
	else if (_pScreen->_isSDW)
	{
		iTimeX1 = _pScreen->x(507); iTimeY1 = _pScreen->y(635);
		iTimeX2 = _pScreen->x(507+364); iTimeY2 = _pScreen->y(635+24);

		iExpX1 = _pScreen->x(507); iExpY1 = _pScreen->y(674);
		iExpX2 = _pScreen->x(507+364); iExpY2 = _pScreen->y(674+24);
	}
	else if (_pScreen->_isHDW)
	{
		iTimeX1 = _pScreen->x(711); iTimeY1 = _pScreen->y(895);
		iTimeX2 = _pScreen->x(711 + 510); iTimeY2 = _pScreen->y(895 + 30);

		iExpX1 = _pScreen->x(711); iExpY1 = _pScreen->y(951);
		iExpX2 = _pScreen->x(711 + 510); iExpY2 = _pScreen->y(951 + 30);
	}
	else if (_pScreen->_isHDS)
	{
		iTimeX1 = _pScreen->x(670); iTimeY1 = _pScreen->y(1272);
		iTimeX2 = _pScreen->x(1400); iTimeY2 = _pScreen->y(1314);

		iExpX1 = _pScreen->x(670); iExpY1 = _pScreen->y(1350);
		iExpX2 = _pScreen->x(1400); iExpY2 = _pScreen->y(1400);
	}

	// szare progress bary jako podklad

	m_pGreyBar->Position(iTimeX1,iTimeY1);
	m_pGreyBar->Resize(iTimeX1,iTimeY1,iTimeX2,iTimeY2);
	m_pGreyBar->Render();

	m_pGreyBar->Position(iExpX1,iExpY1);
	m_pGreyBar->Resize(iExpX1,iExpY1,iExpX2,iExpY2);
	m_pGreyBar->Render();

	// rysujemy pasek czasu

	fCurrent = 1000 - fTimeBar;
	fCurrent =  fCurrent*0.001f;		// skala 1-100

	m_pTimeBar->Position(iTimeX1,iTimeY1);
	m_pTimeBar->Resize(iTimeX1,iTimeY1,(int)iTimeX1+((iTimeX2-iTimeX1)*fCurrent),(int)iTimeY1+(iTimeY2-iTimeY1));
	m_pTimeBar->Render();

	// rysujemy pasek doswiadczenia

	fCurrent = (float)(m_ulBonusExp/10);

	if (fCurrent>1000)	// czy awansujemy ?
	{
		m_ulBonusExp = 0;
		
		if (m_ucScoreMulti!=9)	// _level up
		{
			m_ucScoreMulti++;
			m_pPopup->Add(POPUP_FLASH_WHITE,(unsigned long)ulTimer);
			_iLevelUpChannel = Mix_PlayChannel(-1, _pMLevelUp,0);
		}
		m_ulBonusTime +=1000;	// dodajemy graczowi czas przy awansie
	}

	fCurrent = fCurrent*0.001f;

	m_pExpBar->Position(iExpX1,iExpY1);
	m_pExpBar->Resize(iExpX1,iExpY1,(int)iExpX1+((iExpX2-iExpX1)*fCurrent),(int)iExpY1+(iExpY2-iExpY1));
	m_pExpBar->Render();

}

//=== rysuje pojedyncza klatke
//=== TODO: extra klocki dostepne proporcjonalnie do _levelu

int CIngame::Render(unsigned long ulTimer, CTouch *pTouch)
{
	int 	iReturn,h1,h2,h3,h4;
	char 	c1,c2;
	char	cScore[8];	//	do konwersji na digits

	iReturn = 0;

	if (m_ulTimerStart == 0)		// czy to pierwsza renderowana klatka ?
	{
		m_ulTimerStart = ulTimer;
		m_lHintTime = ulTimer;

		if (pTouch->_isTouch)	// nie przechwytujmy clicku z menu
			m_bMouseLock = true;

		m_pPopup->Add(POPUP_INGAME_START,ulTimer);

		if (_pScreen->_isSDS)
		{
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(850), _pScreen->y(640), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(140), _pScreen->y(640), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(885), _pScreen->y(420), 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod _levelem
		}
		else if (_pScreen->_isSDW)
		{
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(1015), _pScreen->y(640), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(315), _pScreen->y(640), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(1080), _pScreen->y(400), 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod _levelem
		}
		else if (_pScreen->_isHDW)
		{
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(1420), _pScreen->y(888), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(440), _pScreen->y(888), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(1500), _pScreen->y(600), 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod _levelem
		}
		else if (_pScreen->_isHDS)
		{
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(1900), _pScreen->y(1200), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod latarni¹
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(600), _pScreen->y(1150), 1.0f, 0.75f, 0.5f, 1, ulTimer, 100000);	// particle pod przyciskiem menu
			_pFXManager->Add(FX_SMALL_LOOP, _pScreen->x(2050), _pScreen->y(600), 0.0f, 0.0f, 0.0f, 1.0f, ulTimer, 100000);	// particle pod _levelem
		}

	}

	m_pBackground->Render();
	m_pParticleManager->Render(ulTimer);

	_pFXManager->Render(ulTimer, FX_LAYER_0);

	m_pBoard->RenderC();

	DrawProgressBar(ulTimer);

	// sprawdzamy czy trzeba zmienic delte klockow

	if (!m_bGameOver)
		m_bFallLock = isMoveGems(ulTimer);

	if (m_bFallLock)			// zapamietaj czas ostatniego ruchu, jezeli brak ruchu przez 5 sekund to daj podpowiedz
		m_lHintTime = ulTimer;

	// sprawdzamy czy przycisk mozemy odblokowac

	if (m_bMouseLock && !pTouch->_isTouch)
		m_bMouseLock=false;

	// sprawdz czy sa trojki

	if (!m_bFallLock) 
		isMatch3(ulTimer);

	// jezeli cala dolna linia to same kamienie, to kasujemy t¹ linie

	if (m_cBoard[63] == m_cBoard[62] == m_cBoard[61] == m_cBoard[60] == m_cBoard[59] == m_cBoard[58] == m_cBoard[57] == m_cBoard[58] == GEM_ROCK)
		m_bBoard[63] = m_bBoard[62] = m_bBoard[61] = m_bBoard[60] = m_bBoard[59] = m_bBoard[58] = m_bBoard[57] = m_bBoard[58] = true;

	// kasujemy dopasowane klocki, true = puste pole

	for (h1=0; h1<64; h1++)
	{
		if (m_bBoard[h1])
			m_cBoard[h1]=-1;		
	}

	// scroll z gory na dol - klocki opadaja

	if (!m_bFallLock)
	{
		for (h1=7; h1>=1; h1--)	// sprawdzamy pionowo od do³u do góry
		{
			if (!m_bFallLock)
			{
				for (h2=0; h2<=7; h2++)
				{
					if (m_bBoard[(h1*8)+h2] == true && m_bBoard[((h1-1)*8)+h2]==false)
					{
						m_bBoard[(h1*8)+h2] = false; 
						m_bBoard[((h1-1)*8)+h2] = true;			
						m_cBoard[(h1*8)+h2] = m_cBoard[((h1-1)*8)+h2];
						m_cBoard[((h1-1)*8)+h2]=-1;	
						m_fBoardDeltaY[(h1 * 8) + h2] = -_ucGemSize;
					}
				}
			}
		}

		// uzupelniamy gorna linie

		for (h1=0; h1<=7; h1++)
		{
			if (m_bBoard[h1])
			{
				m_bBoard[h1]=false;
				
				if (m_ucScoreMulti<5)		// jezeli etap mniejszy od 5 to dodajemy tylko podstawowe klocki
				{
					m_cBoard[h1]=rand()%7;
				}
				else
				{
					m_cBoard[h1]=rand()%9;		// 8 to kamyk
					if (m_cBoard[h1]==8)		// 9 trzeba zamienic na 11 - bomba i zmniejszyc szanse jej pojawienia sie na 1/5
					{
						if (rand()%5==3)
						{
							m_cBoard[h1]=GEM_BOMB;
						}
						else
						{
							m_cBoard[h1]=rand()%7;
						}
					}
				}
				m_fBoardDeltaY[h1] = -_ucGemSize;
			}
		}
	}

	// narysuj przeskalowane poprzednie klocki

	h3 = _ucGemSize;
	h4 = h3/2;

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (m_cScaleBoard[(h1*8)+h2]!=-1)
			{
				if ((ulTimer-m_ulScaleTimer[(h1*8)+h2])<100.0f)
				{
					float scale = (1+(((float)(ulTimer-m_ulScaleTimer[(h1*8)+h2])/100.0f)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Position((float)(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3)+h4-(h4*scale)),(float)(_uiBoardOffsetY+(h3*h1)+h4-(h4*scale)));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Scale(scale,scale);
					
					scale = scale - 1.0f;

					m_pGem[m_cScaleBoard[(h1*8)+h2]]->_fAlfa=(1.0f-(1.0f*scale));
					m_pGem[m_cScaleBoard[(h1*8)+h2]]->Render();
				}
				else
				{
					m_cScaleBoard[(h1*8)+h2]=-1;
				}
			}
		}
	}

	// narysuj tablice oraz monety

	for (h1=0; h1<8; h1++)
	{
		for (h2=0; h2<8; h2++)
		{
			if (m_cBoard[(h1*8)+h2]>-1)
			{
				if (m_cBoard[(h1*8)+h2]<GEM_ROCK)
				{
					m_pGem[m_cBoard[(h1*8)+h2]]->Position((float)(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
					m_pGem[m_cBoard[(h1*8)+h2]]->Scale(1.0f,1.0f);
					m_pGem[m_cBoard[(h1*8)+h2]]->_fAlfa=(1.0f);
					m_pGem[m_cBoard[(h1*8)+h2]]->Render();
				}

				if (m_cBoard[(h1*8)+h2]==GEM_RAINBOW)
				{
					_pGemRainbow->Render(((ulTimer+(100*h1*h2))/10)%_pGemRainbow->iFrameCount(),(float)(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}

				if (m_cBoard[(h1*8)+h2]==GEM_DIAMOND)
				{
					_pGemDiamond->Render(((ulTimer+(100*h1*h2))/10)%_pGemDiamond->iFrameCount(),(float)(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}

				if (m_cBoard[(h1*8)+h2]==GEM_ROCK)
				{
					_pGemRock->Render(((ulTimer+(100*h1*h2))/10)%_pGemRock->iFrameCount(),(float)(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}

				if (m_cBoard[(h1*8)+h2]==GEM_BOMB)
				{
					_pGemBomb->Render(((ulTimer+(100*h1*h2))/10)%_pGemBomb->iFrameCount(),(float)(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3)+m_fBoardDeltaX[(h1*8)+h2]),(float)(_uiBoardOffsetY+(h3*h1)+m_fBoardDeltaY[(h1*8)+h2]));
				}
			}

			// czy rysujemy monety nad klockami

			if (m_iCoin[(h1*8)+h2]!=-1)
			{
				if ((ulTimer - m_iCoin[(h1*8)+h2])>100.0f) // czy minal czas 255 ? 
				{
					m_iCoin[(h1*8)+h2]=-1;	// zerujemy 
				}
				else
				{
					float fAlfa = ((((float)(ulTimer-m_iCoin[(h1*8)+h2])/100.0f)));

					if (_sCoin[(h1*8)+h2]==100)
					_pScore100->Render(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

					if (_sCoin[(h1*8)+h2]==250)
					_pScore250->Render(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

					if (_sCoin[(h1*8)+h2]==500)
					_pScore500->Render(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

					if (_sCoin[(h1*8)+h2]==1000)
					_pScore1000->Render(((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2))+(h2*h3),_uiBoardOffsetY+(h3*h1)- (ulTimer - m_iCoin[(h1*8)+h2]), 1.0f-(1.0f*fAlfa));

				}
			}
		}
	}

	// jezeli przesuniecie jest wieksze od +/- 64 to zdejmujemy blokade myszy

	if (pTouch->iDeltaX()>_ucGemSize || pTouch->iDeltaY()>_ucGemSize || pTouch->iDeltaX()<-_ucGemSize || pTouch->iDeltaY()<-_ucGemSize)
	{
		m_bMouseLock = false;
		pTouch->iStartX(pTouch->iX());
	    pTouch->iStartY(pTouch->iY());
	}

	// czy kliknieto

	h3 = _ucGemSize;

	if (pTouch->iX()>((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)) && pTouch->iX()<((_pScreen->_iSizeX/2)+(m_pBoard->_fSizeX/2)) &&
		pTouch->iY()>_uiBoardOffsetY && pTouch->iY()<(m_pBoard->_fSizeX+_uiBoardOffsetY) && pTouch->_isTouch && !m_bMouseLock && !m_bGameOver && !m_bFallLock)
	{
		h1 = (int)((pTouch->iX()-((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)))/h3);	// X na tablicy
		h2 = (int)((pTouch->iY()-_uiBoardOffsetY)/h3);	// Y na tablicy

		if (m_cClickedA==-1)
		{
			m_cClickedA=(h2*8)+h1;
			m_iClickedAx = ((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)) +(h1*h3);
			m_iClickedAy = _uiBoardOffsetY + (h2*h3);
		}
		else if (m_cClickedB==-1)
		{
			if (m_cClickedA!=(h2*8)+h1)			// czy to nie ten sam co #1 ? 
			{
				if ( (((m_cClickedA-1 == (h2*8)+h1) || (m_cClickedA+1 == (h2*8)+h1)) && m_iClickedAy == _uiBoardOffsetY + (h2*h3)) || (m_cClickedA+8 == (h2*8)+h1) || (m_cClickedA-8 == (h2*8)+h1) ) // czy to klik obok ?
				{					
					m_cClickedB=(h2*8)+h1;			// numer kliknietego klocka B na tablicy
					m_iClickedBx = ((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)) +(h1*h3);	// wspolrzedne X klocka B
					m_iClickedBy = _uiBoardOffsetY + (h2*h3);	// wspolrzedne Y klocka B
				}
				else	// to nie jest click obok wiêc to bêdzie teraz nasz klocek #1
				{
					m_cClickedA=(h2*8)+h1;
					m_iClickedAx = ((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)) +(h1*h3);
					m_iClickedAy = _uiBoardOffsetY + (h2*h3);
				}
			}
			else	// jesli to samo to kasujemy zaznaczenie
			{
				m_cClickedA = -1;
				m_cClickedB = -1;
				m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 		
			}
		}	

		// jezeli ktorys z kliknietych kamykow to skala to kasujemy zaznaczenia

		if (m_cBoard[m_cClickedA]==GEM_ROCK || m_cBoard[m_cClickedB]==GEM_ROCK)
		{
			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 				
		}

		// jezeli ktorys z klikniety kamykow to bomba, to wybuchamy klocki 

		if (m_cBoard[m_cClickedA]==GEM_BOMB || m_cBoard[m_cClickedB]==GEM_BOMB)
		{
				_iBombChannel = Mix_PlayChannel(-1, _pMBomb,0);

				if (m_cBoard[m_cClickedA] == GEM_BOMB)
				{
					_pFXManager->Add(FX_BIG_EXPLOSION, m_iClickedAx + (h3 / 2), m_iClickedAy + (h3 / 2), (25+ ((ulTimer * m_iClickedAx) % 75)) * 0.01f, (25 + ((ulTimer * m_iClickedAy) % 75)) * 0.01f, (25 + ((ulTimer * m_ulScore) % 75)) * 0.01f, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
				}
				else
				{
					_pFXManager->Add(FX_BIG_EXPLOSION, m_iClickedBx + (h3 / 2), m_iClickedBy + (h3 / 2), (25 + ((ulTimer * m_iClickedBx) % 75)) * 0.01f, (25 + ((ulTimer * m_iClickedBy) % 75)) * 0.01f, (25 + ((ulTimer * m_ulScore) % 75)) * 0.01f, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
				}

				m_cBoard[(h2*8)+h1] = -1;
				m_bBoard[(h2*8)+h1] = true;
				m_iCoin[(h2*8)+h1] = ulTimer;
				_sCoin[(h2*8)+h1] = 500;
				Advance(0,50,500);
				
				if (h1>0)	// po lewej
				{
					m_cBoard[(h2*8)+h1-1] = -1;
					m_bBoard[(h2*8)+h1-1] = true;
					m_iCoin[(h2*8)+h1-1] = ulTimer;
					_sCoin[(h2*8)+h1-1] = 100;
				}					

				if (h1<7)	// po prawej
				{
					m_cBoard[(h2*8)+h1+1] = -1;
					m_bBoard[(h2*8)+h1+1] = true;
					m_iCoin[(h2*8)+h1+1] = ulTimer;
					_sCoin[(h2*8)+h1+1] = 100;
				}			

				if (h2>0)	// na gorze
				{
					m_cBoard[((h2-1)*8)+h1] = -1;
					m_bBoard[((h2-1)*8)+h1] = true;
					m_iCoin[((h2-1)*8)+h1] = ulTimer;			
					_sCoin[((h2-1)*8)+h1] = 100;
				}

				if (h2<7) // na dole
				{
					m_cBoard[((h2+1)*8)+h1] = -1;
					m_bBoard[((h2+1)*8)+h1] = true;
					m_iCoin[((h2+1)*8)+h1] = ulTimer;
					_sCoin[((h2+1)*8)+h1] = 100;			
				}

				if (h1>0 && h2>0)	// na gorze po lewej
				{
					m_cBoard[((h2-1)*8)+h1-1] = -1;
					m_bBoard[((h2-1)*8)+h1-1] = true;
					m_iCoin[((h2-1)*8)+h1-1] = ulTimer;					
					_sCoin[((h2-1)*8)+h1-1] = 100;					
				}

				if (h2>0 && h1<7)	// na gorze po prawej
				{
					m_cBoard[((h2-1)*8)+h1+1] = -1;
					m_bBoard[((h2-1)*8)+h1+1] = true;
					m_iCoin[((h2-1)*8)+h1+1] = ulTimer;
					_sCoin[((h2-1)*8)+h1+1] = 100;					
				}

				if (h2<7 && h1>0)	// na dole po lewej
				{
					m_cBoard[((h2+1)*8)+h1-1] = -1;
					m_bBoard[((h2+1)*8)+h1-1] = true;
					m_iCoin[((h2+1)*8)+h1-1] = ulTimer;
					_sCoin[((h2+1)*8)+h1-1] = 100;
				}

				if (h1<7 && h2<7)	// na dole po prawej
				{
					m_cBoard[((h2+1)*8)+h1+1] = -1;
					m_bBoard[((h2+1)*8)+h1+1] = true;
					m_iCoin[((h2+1)*8)+h1+1] = ulTimer;
					_sCoin[((h2+1)*8)+h1+1] = 100;
				}			

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 						
		}

		// jezeli ktorys z kamykow to diament to kasujemy linie w pionie i w poziomie

		if (m_cBoard[m_cClickedA]==GEM_DIAMOND || m_cBoard[m_cClickedB]==GEM_DIAMOND)
		{
			_iDiamondChannel = Mix_PlayChannel(-1, _pMDiamond,0);

			// dodajemy monete tylko tam gdzie jest diament

			if (m_cBoard[m_cClickedA]==GEM_DIAMOND)
			{
				m_iCoin[m_cClickedA] = ulTimer;
				_sCoin[m_cClickedA] = 500;
				Advance(0,50,500);
			}
			else
			{
				m_iCoin[m_cClickedB] = ulTimer;
				_sCoin[m_cClickedB] = 100;
				Advance(0,50,500);
			}

			// kasujemy w poziomie i w pionie

			for (int i=0; i<8; i++)
			{
				m_cScaleBoard[(h2*8)+i] = m_cBoard[(h2*8)+i];
				m_ulScaleTimer[(h2*8)+i] = (unsigned long)ulTimer;

				m_cScaleBoard[(i*8)+h1] = m_cBoard[(i*8)+h1];
				m_ulScaleTimer[(i*8)+h1] = (unsigned long)ulTimer;

				m_cBoard[(h2*8)+i] = -1;
				m_bBoard[(h2*8)+i] = true;

				m_cBoard[(i*8)+h1] = -1;
				m_bBoard[(i*8)+h1] = true;

				_pFXManager->Add(FX_DIAMOND_EXPLOSION, ((_pScreen->_iSizeX / 2) - (m_pBoard->_fSizeX / 2)) + (h1*h3) + (h3 / 2), _uiBoardOffsetY + (i*h3) + (h3/ 2), 1, 1, 1, 1, ulTimer, 2000, FX_LAYER_5);
				_pFXManager->Add(FX_DIAMOND_EXPLOSION, ((_pScreen->_iSizeX / 2) - (m_pBoard->_fSizeX / 2)) + (i*h3) + (h3 / 2), _uiBoardOffsetY + (h2*h3) + (h3/ 2), 1, 1, 1, 1, ulTimer, 2000, FX_LAYER_5);

			}

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 						
		}

		m_bMouseLock = true;	// zablokuj myszke zeby w nastepnej klatce nie chwycil tego samego 

	}

	// rysowanie oznaczenia na kamykach

	if (m_iClickedAx!=-1)
	{
		m_pHint->Position((float)m_iClickedAx, (float)m_iClickedAy);
		m_pHint->_fRotation=0.f;
		m_pHint->Render();
	}

	if (m_iClickedBx!=-1)
	{
		m_pHint->Position((float)m_iClickedBx,(float)m_iClickedBy);
		m_pHint->_fRotation=0.f;
		m_pHint->Render();
	}

	// zamiana kamykow kolejnoscia

	if (m_cClickedA!=-1 && m_cClickedB!=-1)	
	{
		// jezeli jeden z zaznaczonych kamykow to teczowy to usuwamy wszystkie tego typu kamyki z planszy jak drugi typ

		if (m_cBoard[m_cClickedA] == GEM_RAINBOW || m_cBoard[m_cClickedB] == GEM_RAINBOW)
		{
			_iRainbowChannel = Mix_PlayChannel(-1, _pMRainbow,0);

			if (m_cBoard[m_cClickedA] == GEM_RAINBOW)
			{
				h2 = m_cBoard[m_cClickedB]; // zapamietaj do kasowania

				for (h1 = 0; h1 < 8; h1++)
				{
					for (h3 = 0; h3 < 8; h3++)
					{
						if (m_cBoard[(h1*8)+h3] == h2)
						{
							m_cBoard[(h1 * 8) + h3] = -1;
							m_bBoard[(h1 * 8) + h3] = true;
							m_iCoin[(h1 * 8) + h3] = ulTimer;	// dodajemy monete
							_sCoin[(h1 * 8) + h3] = 100;
							Advance(0, 10, 100);

							_pFXManager->Add(FX_RAINBOW_EXPLOSION, ((_pScreen->_iSizeX / 2) - (m_pBoard->_fSizeX / 2)) + (h3*_ucGemSize) + _ucGemSizeHalf, _uiBoardOffsetY + (h1*_ucGemSize) + _ucGemSizeHalf, 1, 1, 1, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
						}
					}
				}
				m_cBoard[m_cClickedA] = -1;
				m_bBoard[m_cClickedA] = true;
				m_iCoin[m_cClickedA] = ulTimer;
				_sCoin[m_cClickedA] = 1000;
				Advance(0,100,1000);
			}
			else
			{
				h2 = m_cBoard[m_cClickedA];

				for (h1 = 0; h1 < 8; h1++)
				{
					for (h3 = 0; h3 < 8; h3++)
					{
						if (m_cBoard[(h1 * 8) + h3] == h2)
						{
							if (m_cBoard[(h1 * 8) + h3] == h2)
							{
								m_cBoard[(h1 * 8) + h3] = -1;
								m_bBoard[(h1 * 8) + h3] = true;
								m_iCoin[(h1 * 8) + h3] = ulTimer;
								_sCoin[(h1 * 8) + h3] = 100;
								Advance(0, 10, 100);

								_pFXManager->Add(FX_RAINBOW_EXPLOSION, ((_pScreen->_iSizeX / 2) - (m_pBoard->_fSizeX / 2)) + (h3*_ucGemSize) + _ucGemSizeHalf, _uiBoardOffsetY + (h1*_ucGemSize) + _ucGemSizeHalf, 1, 1, 1, 1, ulTimer, 1000, FX_LAYER_5);	// particle wybuch bomby
							}
						}
					}
				}

				m_cBoard[m_cClickedB] = -1;
				m_bBoard[m_cClickedB] = true;
				m_iCoin[m_cClickedB] = ulTimer;
				_sCoin[m_cClickedB] = 1000;
				Advance(0,100,1000);
			}

			m_cClickedA = -1;
			m_cClickedB = -1;
			m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 
			m_bMouseLock = true;
		}
	}

	if (m_cClickedA!=-1 && m_cClickedB!=-1)	// swap
	{
		m_bHint = false;		// znikamy pomoc
		
		if (_iHintID != -1)
		{
			_pFXManager->Remove(_iHintID);
			_iHintID = -1;
		}
		
		m_lHintTime = ulTimer;

		// zamiana kolejnoscia
		
		h1=m_cBoard[m_cClickedA];
		m_cBoard[m_cClickedA] = m_cBoard[m_cClickedB];
		m_cBoard[m_cClickedB] = h1;	

		if (!isMatch3Check()) // jak nie ma dopasowania po ruchu to cofamy
		{
			h1=m_cBoard[m_cClickedA];
			m_cBoard[m_cClickedA] = m_cBoard[m_cClickedB];
			m_cBoard[m_cClickedB] = h1;	

			// tutaj jakis event dzwiekowy

		}
		else
		{
			if (abs(m_cClickedA-m_cClickedB)==1)	// czy klocki sa obok siebie w poziomie?
			{
				if (m_cClickedA>m_cClickedB)
				{
					m_fBoardDeltaX[m_cClickedA] = -_ucGemSize; // -64.0f;
					m_fBoardDeltaX[m_cClickedB] = _ucGemSize; // 64.0f;
				}
				else
				{
					m_fBoardDeltaX[m_cClickedA] = _ucGemSize;// 64.0f;
					m_fBoardDeltaX[m_cClickedB] = -_ucGemSize;// 64.0f;
				}
			}
			else	// klocki sa obok siebie w pionie			
			{
				if (m_cClickedA>m_cClickedB)
				{
					m_fBoardDeltaY[m_cClickedA] = -_ucGemSize;// 64.0f;
					m_fBoardDeltaY[m_cClickedB] = _ucGemSize;// 64.0f;
				}
				else
				{
					m_fBoardDeltaY[m_cClickedA] = _ucGemSize;// 64.0f;
					m_fBoardDeltaY[m_cClickedB] = -_ucGemSize;// 64.0f;
				}
			}
		}

		m_cClickedA = -1;
		m_cClickedB = -1;
		m_iClickedAx = m_iClickedAy = m_iClickedBx = m_iClickedBy = -1; 
		m_bMouseLock = true;
	}

	// sprawdzamy czy sa jeszcze mozliwe ruchy
	
	c2=0;

	for (h1=0; h1<=7; h1++) // czy mozliwe ruchy w poziomie
	{
		for (h2=0; h2<=6; h2++)
		{
			if (m_cBoard[(h1*8)+h2]!=-1 && m_cBoard[(h1*8)+h2+1]!=-1 && 
				m_cBoard[(h1*8)+h2]<GEM_ROCK && m_cBoard[(h1*8)+h2+1]<GEM_ROCK)	// sprawdzamy tylko kamyki standardowe
			{
				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[(h1*8)+h2+1];
				m_cBoard[(h1*8)+h2+1] = c1;

			    if (isMatch3Check())
				{
					c2=1;
					m_iHintX = ((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)) + (h2*_ucGemSize);
					m_iHintY = _uiBoardOffsetY + (h1*_ucGemSize);
				}

				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[(h1*8)+h2+1];
				m_cBoard[(h1*8)+h2+1] = c1;
			}
		}
	}

	for (h1=0; h1<=6; h1++) // czy mozliwe ruchy w pionie
	{
		for (h2=0; h2<=7; h2++)
		{
			if (m_cBoard[(h1*8)+h2]!=-1 && m_cBoard[((h1+1)*8)+h2]!=-1 &&
				m_cBoard[(h1*8)+h2]<GEM_ROCK && m_cBoard[((h1+1)*8)+h2]<GEM_ROCK)	// sprawdzamy tylko kamyki standardowe
			{
				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cBoard[((h1+1)*8)+h2] = c1;

			    if (isMatch3Check())
				{
					c2=1;
					m_iHintX = ((_pScreen->_iSizeX/2)-(m_pBoard->_fSizeX/2)) + (h2*_ucGemSize);
					m_iHintY = _uiBoardOffsetY + (h1*_ucGemSize);
				}

				c1 = m_cBoard[(h1*8)+h2];
				m_cBoard[(h1*8)+h2] = m_cBoard[((h1+1)*8)+h2];
				m_cBoard[((h1+1)*8)+h2] = c1;
			}
		}
	}

	if (c2)	// sprawdzamy czy mozemy dac podpowiedz
	{
		if ( ((ulTimer - m_lHintTime)>1000) || m_bHint)
		{
			m_bHint = true;

			if (_iHintID==-1)
				_iHintID = _pFXManager->Add(FX_HINT, (float)m_iHintX + _ucGemSizeHalf, (float)m_iHintY + _ucGemSizeHalf, 1.0f, 1.0f, 1.0f, 1, ulTimer, 1000000,FX_LAYER_5);	// particle wybuch bomby
		}
	}
	else
	{
		if (!m_bFallLock) // nie ma ruchow mozliwych
		{
			// zamieniamy to na postawienie krysztalowego klocka w losowym miejscu na planszy
			bool bSpecial=false;

			for (int i=0; i<64; i++)
			{
				if (m_cBoard[i] == GEM_RAINBOW || m_cBoard[i] == GEM_DIAMOND || m_cBoard[i] == GEM_BOMB)
					bSpecial = true;
			}

			// jezeli na planszy nie ma zadnego klocka specjalnego to zamieniamy jeden na teczowy

			if (!bSpecial)
			{
				int i = ulTimer % 7;
				m_cBoard[(i<<3)+i] = GEM_BOMB;

				_pFXManager->Add(FX_SHOW_BOMB, (_pScreen->_iSizeX / 2) - (m_pBoard->_fSizeX/2 ) + (i*_ucGemSize) + _ucGemSizeHalf, _uiBoardOffsetY + (i*_ucGemSize) + _ucGemSizeHalf, 1, 1, 1, 1, ulTimer, 2000, FX_LAYER_5);
				_iRainbowChannel = Mix_PlayChannel(-1, _pMRainbow,0);
				bSpecial = false;
			}
		}
	}

	// rysujemy licznik punktow

	h3=0;

	// odstep po lewej

	if (_pScreen->_isSDS)
	{
		h3 = _pScreen->x(16);
		h4 = 32;	// odstep pomiedzy cyferkami
	}
	else if (_pScreen->_isSDW)
	{
		h3 = _pScreen->x(64);
		h4 = 32;
	}
	else if (_pScreen->_isHDW)
	{
		h3 = _pScreen->x(64);
		h4 = 64;
	}
	else if (_pScreen->_isHDS)
	{
		h3 = _pScreen->x(32);
		h4 = 64;
	}
	
	h2 = _pScreen->_iSizeY / 2;

	sprintf(cScore,"%.7d",m_ulScore);

	for (int i=0; i<7; i++)
	{
		m_pNumber[cToDigit(cScore[i])]->Position(h3+(i*h4),h2);
		m_pNumber[cToDigit(cScore[i])]->Render();
	}

	// dodatkowe particle - hint

	_pFXManager->Render(ulTimer, FX_LAYER_5);

	// rysujemy game over

	if (m_bGameOver)
	{
		if (m_lInGameOver==0)
			m_lInGameOver=ulTimer;

		m_pGameOver->Render();

		if (ulTimer-m_lInGameOver>500)	// wychodzimy z gry
			iReturn = -1;		

		if (!_isGameOverSFX)			// pierwszy render game over -> odtworz dzwiek
		{
			_isGameOverSFX = true;
			Mix_HaltMusic();
			Mix_PlayChannel(-1, _pGameOverSFX, 0);
		}

	}

	// przyciski menu i hint, score multi info, jezeli nie ma gameover

	if (!m_bGameOver)
	{
		if (m_pButtonMenu->Render(pTouch)==ON_LEFT)
			iReturn = -1; 

		if (m_pButtonHint->Render(pTouch)==ON_LEFT && !m_bMouseLock)
		{
			if (!m_bHint)
			{
				m_bHint = true;
				m_ulScore = (unsigned long)(m_ulScore * 0.9);	// zabieramy 10% punktow
				m_bMouseLock = true;

				if (_iHintID != -1)
					_pFXManager->Remove(_iHintID);

			}
		}	

		// renderowanie mnoznika dla punktow

		if (_pScreen->_isSDS)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(_pScreen->x(850), _pScreen->_iSizeY / 2);
		}
		else if (_pScreen->_isSDW)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(_pScreen->x(1050), _pScreen->_iSizeY / 2);
		}
		else if (_pScreen->_isHDW)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(_pScreen->x(1450), _pScreen->_iSizeY / 2);
		}
		else if (_pScreen->_isHDS)
		{
			m_pScoreMulti[m_ucScoreMulti]->Position(_pScreen->x(1700), _pScreen->_iSizeY / 2 );
		}

		
		m_pScoreMulti[m_ucScoreMulti]->Render();

	}

	m_ulPrevTimer = ulTimer;		// zapamietaj czas ostatniej klatki

	m_bPrevFallLock = m_bFallLock;

	// sprawdzamy roznice punktow w ciagu ostatnich 10 sekund, jezeli jest wystarzcajaco duza to dajemy popup

	if (m_ulScore != m_ulScore1000 && m_ulScore > m_ulScore1000)		// zmienily sie punkty, wiec sprawdzamy czy w ciagu 10 sekund nabilismy 100, pomijamy przypadek gdy gracz ma mniej punktow niz poprzednio bo nacisnal hint
	{
		if ((ulTimer-m_ulTimer1000)>1000)	// minelo 10 sekund, przepisujemy timer i punkty do nowego
		{
			m_ulTimer1000 = ulTimer;
			m_ulScore1000 = m_ulScore;
		}
		else
		{
			if ((m_ulScore-m_ulScore1000) > (1000+(1000 * m_ucScoreMulti)))	// nie minelo 10 sekund, jezeli roznica punktow > 100 to dajemy popup
			{
				switch(ulTimer%5)
				{
					case 0:
						m_pPopup->Add(POPUP_INGAME_GOOD1,(unsigned long)ulTimer);
					break;

					case 1:
						m_pPopup->Add(POPUP_INGAME_GOOD2,(unsigned long)ulTimer);
					break;

					case 2:
						m_pPopup->Add(POPUP_INGAME_GOOD3,(unsigned long)ulTimer);
					break;

					case 3:
						m_pPopup->Add(POPUP_INGAME_GOOD4,(unsigned long)ulTimer);
					break;

					case 4:
						m_pPopup->Add(POPUP_INGAME_GOOD5,(unsigned long)ulTimer);
					break;
				}
				_iSuperChannel = Mix_PlayChannel(-1,_pMSuper,0);
				m_ulTimer1000 = ulTimer;
				m_ulScore1000 = m_ulScore;
			}
		}
	}

	// renderujemy popup jezeli jakis jest

	if (!m_bGameOver)
	{
		m_pPopup->Render(ulTimer);
	}

	return iReturn;
}

unsigned long CIngame::ulGetScore(void)		// zwraca liczbe punktow z tej serii
{
	return m_ulScore;
}

void CIngame::AddScore(long lScore)		// dodaje liczbe punktow
{
	m_ulScore += lScore;
}

void CIngame::mute(void)
{
	Mix_HaltChannel(_iSuperChannel);
	Mix_HaltChannel(_iRainbowChannel);
	Mix_HaltChannel(_iDiamondChannel);
	Mix_HaltChannel(_iLevelUpChannel);
	Mix_HaltChannel(_iClickChannel);
	Mix_HaltChannel(_iBombChannel);
	Mix_HaltChannel(_iTikTakChannel);
}

//end
