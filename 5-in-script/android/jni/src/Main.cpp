#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <jni.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "SDL.h"
#include "../SDL_mixer/SDL_mixer.h"
#include "Main.h"

#include "control/Touch.h"

#include "gfx/Screen.h"					// obsluga ekranu
#include "gfx/Sprite.h"
#include "gfx/Button.h"
#include "gfx/SpriteFont.h"
#include "gfx/MobileKeyboard.h"

//=== ui

#include "application/Intro.h"
#include "application/MainMenu.h"
#include "application/Ingame.h"

// stany aplikacji

CIntro				*pIntro;
CMainMenu			*pMainMenu;
CIngame				*ingame;

//=== zmienne globalne

int					iAppState;			// aktualny stan aplikacji
int					iPrevAppState; 		// poprzedni stan aplikacji

CScreen				*pScreen;			// ekran

CTouch				*pTouch;			// dane z ekranu dotykowego

// grafiki do preload screen

CSprite	*pLoadScreen;
CSprite *pGreyBar;
CSprite *pGreenBar;

// czcionka

// CSpriteFont *pSpriteFont;

//=== zdarzenia

bool 				isEvent;			// ekran odświeżany jest tylko po tym jak wystąpił jakiś event
SDL_Event 			event;
int					iEvent;				// identyfikator zdarzenia z uiMain

// timery do liczenia klatek

int iFrames, iFPS;
unsigned long ulTimer;	// main application timer
unsigned long ulTimerLast;

char cBuffer[64];

int		iLoad;

//=== muzyka

Mix_Music *pMusicIngame, *pMusicMenu;

// load screen - wyswietla sie w trakcie wczytywania danych

void LoadScreen(int iProgress)
{
	int x1,x2,y1,y2, dx, dy;
	float fx;

	pLoadScreen->Render();

	if (pScreen->_isSDW)
	{
		x1 = pScreen->x(387);
		y1 = pScreen->y(490);

		x2 = pScreen->x(387+592);
		y2 = pScreen->y(490+36);
	}
	else if (pScreen->_isSDS)
	{
		x1 = pScreen->x(207);
		y1 = pScreen->y(480);

		x2 = pScreen->x(820);
		y2 = pScreen->y(511);
	}
	else if (pScreen->_isHDW)
	{
		x1 = pScreen->x(542);
		y1 = pScreen->y(684);

		x2 = pScreen->x(542+839);
		y2 = pScreen->y(684+52);
	}
	else if (pScreen->_isHDS)
	{
		x1 = pScreen->x(419);
		y1 = pScreen->y(960);

		x2 = pScreen->x(1641);
		y2 = pScreen->y(960+70);
	}

	dx = x2-x1;
	dy=y2-y1;

	pGreyBar->Resize(x1,y1,x2,y2);
	pGreyBar->Render();

	fx = (float)(dx * (iProgress*0.01f));

	pGreenBar->Resize(x1,y1,x1+(int)fx,y2);
	pGreenBar->Render();

}

//=== wczytaj konfiguracje z pliku

void loadGameConfig(void)
{
/*
	FILE	*plik;
	char linia[1024];

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
		printf("ERROR: no script file %s\n",SCRIPT_FILE);

	while (strcmp(linia,"<END>"))
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<GAME>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
			UpOnly(linia);

			iMode = 0;

			if (!strcmp(linia,"FULLSCREEN")) iMode=1;
			if (!strcmp(linia,"AUTO")) iMode=2;

			fscanf(plik,"%d %d\n",&iScreenX,&iScreenY);	// wczytaj parametry ekranu
		} // if
	} // while <end>

	fclose(plik);
*/
}


//=== wczytaj ustawienia

void reloadSettings(void)
{
	// wczytaj config
/*
	CGameSettings *pSetup;

	pSetup = new CGameSettings();
	pSetup->bLoad();

	bSettingsMSX = pSetup->isMSX();
	bSettingsSFX = pSetup->isSFX();

	delete pSetup;
*/
}

// przelacz pomiedzy stanami

void state(int i)
{
	iPrevAppState = iAppState;
	iAppState = i;
}

//=== MAIN ===

int main(int argc, char *argv[])
{
	iAppState = E_MAINMENU;
	state(E_INTRO);

	// inicjalizacja audio

	if (SDL_Init(SDL_INIT_AUDIO)<0)
	{
		printf("ERROR: unable to init audio\n");
		exit(1);
	}

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	Mix_AllocateChannels(8);

	loadGameConfig();

	// inicjalizacja grafiki

	pTouch = new CTouch();
	pScreen = new CScreen();

	// inicjalizacja stanow

	pIntro = new CIntro(pScreen);
	pMainMenu = new CMainMenu(pScreen);
	ingame = new CIngame();

	// czcionka glowna

//	pSpriteFont = new CSpriteFont(pMainScreen);

	// sprawdz ustawienia

	reloadSettings();

	// ekran wczytywania danych

	pLoadScreen = new CSprite(pScreen,(char*)"e_mmenu");
	pLoadScreen->Fullscreen(pScreen);

	pGreyBar = new CSprite((char*)"bar_grey.png");
	pGreenBar = new CSprite((char*)"bar_green.png");

	// ekran w trakcie wczytywania muzyki itd

	iLoad = 0;// progress bar, zeby nie przenosil z poprzedniego stanu

	SDL_Log("=== APPLICATION START ===\n");

	// load music

	pMusicIngame = Mix_LoadMUS("music_ingame.ogg");

	pMusicMenu = Mix_LoadMUS("music_mainmenu.ogg");

	// zerowanie eventow

	isEvent = true;
	ulTimer = SDL_GetTicks();

	while (iAppState != E_QUIT)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					iAppState = E_QUIT;
				break;

				case SDL_KEYDOWN:
					iAppState = E_QUIT;
				break;

				case SDL_FINGERDOWN:
					pTouch->Update(true, event.tfinger.x * pScreen->_iSizeX, event.tfinger.y * pScreen->_iSizeY);
					isEvent = true;
				break;

				case SDL_FINGERMOTION:
					pTouch->Update(true, event.tfinger.x * pScreen->_iSizeX, event.tfinger.y * pScreen->_iSizeY);
					isEvent = true;
				break;

				case SDL_FINGERUP:
					pTouch->Update(false, event.tfinger.x * pScreen->_iSizeX, event.tfinger.y * pScreen->_iSizeY);
					isEvent = true;
				break;

                case SDL_APP_DIDENTERFOREGROUND:
                    SDL_Log("SDL_APP_DIDENTERFOREGROUND");
                    Mix_VolumeMusic(100);
                break;

                case SDL_APP_DIDENTERBACKGROUND:
                    SDL_Log("SDL_APP_DIDENTERBACKGROUND");
                    Mix_VolumeMusic(0);

                    if (iAppState==E_INGAME)	// wycisz efekty specjalne
                    	ingame->mute();

                break;

                case SDL_APP_LOWMEMORY:
                    SDL_Log("SDL_APP_LOWMEMORY");
                break;

                case SDL_APP_TERMINATING:
                    SDL_Log("SDL_APP_TERMINATING");
                    Mix_HaltMusic();
                break;

                case SDL_APP_WILLENTERBACKGROUND:
                    SDL_Log("SDL_APP_WILLENTERBACKGROUND");
                break;

                case SDL_APP_WILLENTERFOREGROUND:
                    SDL_Log("SDL_APP_WILLENTERFOREGROUND");
                break;
			}
		}

		switch(iAppState)
		{
			case E_INTRO:

				if (!pIntro->isActive())
				{
					SDL_Log("STATE: E_INTRO");
					pIntro->Open();
					Mix_PlayMusic(pMusicMenu,-1);
				}

				iEvent = pIntro->iRender(ulTimer, pTouch);

				if (iEvent == 1)
				{
					pIntro->Close();
					state(E_MAINMENU);
				}

			break;

			case E_MAINMENU:

				if (!pMainMenu->isActive())
				{
					iLoad = pMainMenu->iOpen();

					if (iLoad == 101)
					{
						if (iPrevAppState == E_INGAME || iPrevAppState == E_POSTGAME)
	                    {
                    		Mix_VolumeMusic(100);
                    		Mix_HaltMusic();
                    		Mix_PlayMusic(pMusicMenu,200);
	                    }
	                    LoadScreen(100);
					}
					else
					{
	                    LoadScreen(iLoad);
					}
				}
	            else	// assety zaladowane - renderowanie
	            {
	                if (pMainMenu->iRender(ulTimer,pTouch)==1)
	                {
	                	pMainMenu->Close();
						Mix_VolumeMusic(0);
	            		Mix_HaltMusic();
	                    state(E_INGAME);
	                }
	            }
			break;

			case E_INGAME :

				if (!ingame->_isActive)
				{
					SDL_Log("STATE: E_INGAME");
					ingame->Open(pScreen);

            		Mix_PlayMusic(pMusicIngame,200);
            		Mix_VolumeMusic(100);
				}
				else
				{
					if (ingame->Render(ulTimer/10,pTouch)!=0)
					{
						ingame->Close();
						Mix_VolumeMusic(0);
	            		Mix_HaltMusic();
	                    state(E_MAINMENU);
					}

				}

			break;

		}

		pScreen->Flip();
		ulTimer = SDL_GetTicks();

	}

	// wyłączenie muzyki

	Mix_FreeMusic(pMusicIngame);
	Mix_FreeMusic(pMusicMenu);

	// usuniecie obiektów

	SafeDelete(pLoadScreen);
	SafeDelete(pGreenBar);
	SafeDelete(pGreyBar);

	SafeDelete(pIntro);
	SafeDelete(pMainMenu);

	delete pTouch;

	delete pScreen;

	exit(0);

}
