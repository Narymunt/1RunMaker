// match3 module 

#pragma once

#include <SDL_mixer.h>
#include "../gfx/Animation.h"
#include "../Main.h"
#include "../GameObject.h"
#include "../control/Touch.h"
#include "../gfx/Particle2DManager.h"
#include "../gfx/Button.h"
#include "../gfx/Popup.h"
#include "../gfx/Screen.h"
#include "../gfx/FXManager.h"

#define GEMS_COUNT	11				// ile ikon kamykow

#define GEM_ROCK	7				// kamyk ktory nie uklada sie we wzory
#define GEM_DIAMOND 8				// diament robi blyskawice w pionie i poziomie
#define GEM_RAINBOW 9				// kamyk tenczowy usuwa wszystkie danego typu z planszy
#define	GEM_BOMB	10				// bomba wybucha kamyki dookola

class CIngame : public CGameObject
{
public:
	CIngame();
	~CIngame();

	void					Open(CScreen *pScreen);					// load data
	void					Close(void);										// unload data 

	int						Render(unsigned long ulTimer,CTouch *pTouch);		// render frame

	bool					isMatch3(unsigned long ulTimer);					// check all combination and generate special gems
	bool					isMatch3Check(void);								// check only for normal gems - used for hint etc. 

	void					Advance(unsigned long ulBonusTime, unsigned long ulBonusExp, unsigned long ulScore);	// add points, exp, time 

	bool					isMoveGems(unsigned long ulTimer);		// update delta x/y 

	void					DrawProgressBar(unsigned long ulTimer);
	char					cToDigit(char cDigit);

	unsigned long			ulGetScore(void);				// return points from this session - used for highscore etc. 
	void					AddScore(long lScore);		// add score

	void					mute(void);	// wycisz wszystkie dzwieki

private:

	float					M3_DELTA;											// predkosc przesuwania klockow

	signed char 			m_cBoard[64];										// 8x8 tutaj sa nasze klocki
	bool					m_bBoard[64];										// false = zostaje, true = do skasowania
	
	float					m_fBoardDeltaX[64];									// dla klockow przesuwanych poziomo
	float					m_fBoardDeltaY[64];									// dla klockow przesuwanych pionowo

	int						m_cClickedA, m_cClickedB;							// ktore klocki ze soba przestawiamy

	int						m_iClickedAx, m_iClickedAy;							// zapamietane wspolrzedne
	int						m_iClickedBx, m_iClickedBy;

	signed char				m_cScaleBoard[64];									// 8x8 informacja o skalowanych klockach, jezeli 255 to nie rysujemy
	float					m_fScaleBoard[64];									// skala klocka
	unsigned long			m_ulScaleTimer[64];									// timer startu
		
	CSprite					*m_pBoard;											// szachownica, podkladka pod kamienie
	unsigned int			_uiBoardOffsetY;									// ile pikseli od gornego rogu ma byc narysowana tablica


	CSprite					*m_pBlack;											// czarne tlo
	CSprite					*m_pBackground;										// tlo

	CSprite					*m_pGem[11];										// obrazki z klockami
	CSprite					*m_pNumber[10];										// cyferki

	CSprite					*m_pTimeBar;										// pokazuje progress czasu
	CSprite					*m_pExpBar;											// doswiadczenie w levelu
	CSprite					*m_pGreyBar;										// szare, zeby bylo wiadomo ile miejsca jest

	unsigned long			m_ulBonusTime;										// dodatkowy czas, ktory pojawia sie, gdy ukladamy klocki
	unsigned long			m_ulBonusExp;										// dodatkowe punkty doswiadczenia

	unsigned long			m_ulTimerStart;										// poczatek
	unsigned long			m_ulPrevTimer;										// zapamietujemy
	unsigned long			m_ulTimer1000;										// zapamietujemy czas 10 sekund temu, jezeli w ciagu 10 sekund nabijemy odpowiednia ilosc punktow to wyskakuje popup

	bool					m_bMouseLock;										// zeby nie lapal tego samego klikniecia na nastepne klatki
	bool					m_bFallLock;										// jezeli klocki spadaja to nie sprawdzamy pionowej kombinacji
	bool					m_bPrevFallLock;									// stan blokady z poprzedniej klatki

	CSprite					*m_pGameOver;										// nakladka na calosc
	bool					m_bGameOver;										// czy koniec gry ?
	long					m_lInGameOver;										// jak dlugo w trybie game over ? 

	CParticle2DManager		*m_pParticleManager;

	CSprite					*m_pHint;											// ramka pokazujaca ktory kamyk przesunac
	
	long					m_lHintTime;										// ile czasu bez ruchu ? 
	bool					m_bHint;											// czy wyswietlamy podpowiedz (po nacisnieciu przycisku)
	int						m_iHintX, m_iHintY;									// wspolrzedne podpowiedzi

	unsigned long			m_ulScore;											// punkty :)
	unsigned long			m_ulScore1000;										// zapamietujemy punkty 10 sekund temu, jezeli w ciagu 10 sekund nabijemy odpowiednia ulosc punktow to wyskakuje popup

	CButton					*m_pButtonMenu;
	CButton					*m_pButtonHint;

	CSprite					*m_pScoreMulti[10];									// mnoznik dla punktow
	unsigned char			m_ucScoreMulti;

	CPopup					*m_pPopup;											// nasz popup manager

	long					m_iCoin[64];										// uzywane do animowania monet wyskakujacych z ulozonych klockow, zawiera timer uruchomienia lub -1 jezeli nie aktywne
	unsigned short			_sCoin[64];											// ile punktow mryga
	CSprite					*_pScore100;	// +100
	CSprite					*_pScore250;	// +250
	CSprite					*_pScore500;	// +500
	CSprite					*_pScore1000;	// +1000

	unsigned int			_uiMatchCount;	// ile combinacji udalo sie juz ulozyc

	CScreen					*_pScreen;

	CAnimation				*_pGemRock;		// 8
	CAnimation				*_pGemDiamond;	// 9
	CAnimation				*_pGemRainbow;	// 10
	CAnimation				*_pGemBomb;		// 11

	// audio samples 

	Mix_Chunk				*_pMSuper;
	int _iSuperChannel;

	Mix_Chunk				*_pMRainbow;
	int _iRainbowChannel;

	Mix_Chunk				*_pMDiamond;
	int _iDiamondChannel;

	Mix_Chunk				*_pMLevelUp;
	int _iLevelUpChannel;

	Mix_Chunk				*_pMClick;
	int _iClickChannel;

	Mix_Chunk				*_pMBomb;
	int _iBombChannel;

	Mix_Chunk				*_pTikTakSFX;											// odliczanie do game over
	bool					_isTikTakSFX;											// czy mamy odtwarzac tiktak
	int						_iTikTakChannel;										// na ktorym kanale gra tik tak

	Mix_Chunk				*_pGameOverSFX;											// sampel wejscia w plansze game over
	bool					_isGameOverSFX;											// czy juz zostal odtworzony?

	CFXManager				*_pFXManager;

	int						_iHintID;												// identyfikator efektu podpowiedzi

	unsigned char			_ucGemSize;												// rozmiar klocka w pixelach
	unsigned char			_ucGemSizeHalf;											// polowa rozmiaru klocka, przydatne przy optymalizacji

	unsigned int			_level;

	bool					_debug;

};

