#include "Popup.h"
#include "../Main.h"

CPopup::CPopup()
{
	_pWhiteFlash = NULL;
	_pBlackFlash = NULL;

	Stop();	// set false to all popups

	_pStart = NULL;

	_pGood1 = NULL;
	_pGood2 = NULL;
	_pGood3 = NULL;
	_pGood4 = NULL;
	_pGood5 = NULL;

	_isActive = false;
}

CPopup::CPopup(char cFile[])
{

}

CPopup::~CPopup()
{
	Close();
}

void CPopup::Open(CScreen *pScreen)
{
	_pWhiteFlash = new CSprite((char*)"white50_1024.png");
	_pWhiteFlash->Fullscreen(pScreen);

	_pBlackFlash = new CSprite((char*)"black.png");
	_pBlackFlash->Fullscreen(pScreen);

	_pStart = new CSprite(pScreen,(char*)"en_popup_start");
	_pStart->Fullscreen(pScreen);

	_pGood1 = new CSprite(pScreen,(char*)"en_popup_excelent");
	_pGood1->Fullscreen(pScreen);

	_pGood2 = new CSprite(pScreen,(char*)"en_popup_good");
	_pGood2->Fullscreen(pScreen);

	_pGood3 = new CSprite(pScreen,(char*)"en_popup_outstanding");
	_pGood3->Fullscreen(pScreen);

	_pGood4 = new CSprite(pScreen,(char*)"en_popup_perfect");
	_pGood4->Fullscreen(pScreen);

	_pGood5 = new CSprite(pScreen,(char*)"en_popup_super");
	_pGood5->Fullscreen(pScreen);

	_pScreen = pScreen;

	_isActive = true;
}

void CPopup::Close(void)
{
	SafeDelete(_pWhiteFlash);
	SafeDelete(_pBlackFlash);

	SafeDelete(_pStart);

	SafeDelete(_pGood1);
	SafeDelete(_pGood2);
	SafeDelete(_pGood3);
	SafeDelete(_pGood4);
	SafeDelete(_pGood5);

	_isActive = false;
}

void CPopup::Add(int iPopupType, unsigned long ulTimer)
{
	int iIndex;

	iIndex = -1;	// look for available spot 

	for (int i=0; i<64; i++)	
	{
		if (_bPopupActive[i]==false && iIndex==-1)
			iIndex = i;
	}

	if (iIndex!=-1)
	{
		_bPopupActive[iIndex] = true;
		_ulTimerStart[iIndex] = ulTimer;
		_iType[iIndex] = iPopupType;
	}

}

void CPopup::Render(unsigned long ulTimer)
{
	for (int i=0; i<64; i++)
	{
		if (_bPopupActive[i])
		{
			switch(_iType[i])
			{
				case POPUP_FLASH_BLACK:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pBlackFlash->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pBlackFlash->Render();
					}
					else
					{					
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_FLASH_WHITE:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pWhiteFlash->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pWhiteFlash->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_FADE_BLACK:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pBlackFlash->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pBlackFlash->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}

				break;

				case POPUP_FADE_WHITE:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pWhiteFlash->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pWhiteFlash->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_START:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pStart->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pStart->_fScaleX=(1.0f + ((float)(ulTimer - _ulTimerStart[i])/500));
						_pStart->Position(_pScreen->_iSizeX/2,_pScreen->_iSizeY/2);
						_pStart->RenderC();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD1:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood1->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood1->_fScaleX=(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood1->Position(_pScreen->_iSizeX/2,_pScreen->_iSizeY/2);
						_pGood1->RenderC();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD2:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood2->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood2->_fScaleY=(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood2->Position(_pScreen->_iSizeX/2,_pScreen->_iSizeY/2);
						_pGood2->RenderC();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD3:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood3->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood3->_fScaleX=(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood3->_fScaleY=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood3->Position(_pScreen->_iSizeX/2,_pScreen->_iSizeY/2);
						_pGood3->RenderC();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD4:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood4->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood4->_fScaleX=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood4->_fScaleY=(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood4->Position(_pScreen->_iSizeX/2,_pScreen->_iSizeY/2);
						_pGood4->RenderC();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD5:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood5->_fAlfa=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood5->_fScaleX=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood5->_fScaleY=(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood5->Position(_pScreen->_iSizeX/2,_pScreen->_iSizeY/2);
						_pGood5->RenderC();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;
			}
		}
	}
}

bool CPopup::isActive(int i)
{
	return _bPopupActive[i];
}

void CPopup::isActive(int i, bool b)
{
	_bPopupActive[i] = b;
}

void CPopup::Stop(void)
{
	for (int i = 0; i < 64; i++)
	{
		_bPopupActive[i] = false;
		_iType[i] = 0;
		_ulTimerStart[i] = 0;
	}
}

void CPopup::Start(void)
{
	for (int i=0; i<64; i++)
		_bPopupActive[i] = true;
}

void CPopup::Stop(int i)
{
	_bPopupActive[i] = false;
}

void CPopup::Start(int i)
{
	_bPopupActive[i] = true;
}

