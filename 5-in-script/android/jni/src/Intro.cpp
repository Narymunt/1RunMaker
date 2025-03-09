#include "Intro.h"

//=== onstruktor

CIntro::CIntro(CScreen *pScreen) :
_pBlack(0),
_pCompanyLogo(0),
_pGameLogo(0)
{

	_pScreen = pScreen;
	_isActive = false;
	_isMouseLock = true;
	_ulTimerStart = 0;
}

//=== destructor 

CIntro::~CIntro()
{
	Close();
}

//=== load and prepare data

void CIntro::Open(void)
{
	_pBlack = new CSprite((char*)"black.png");
	_pBlack->Fullscreen(_pScreen);

	_pCompanyLogo = new CSprite(_pScreen,(char*)"shodan9");
	_pCompanyLogo->Fullscreen(_pScreen);

	_pGameLogo = new CSprite(_pScreen,(char*)"start");
	_pGameLogo->Fullscreen(_pScreen);

	_isActive = true;
	_isMouseLock = true;
	_ulTimerStart = 0;
}

//=== release data

void CIntro::Close(void)
{
	SafeDelete(_pBlack);
	SafeDelete(_pCompanyLogo);
	SafeDelete(_pGameLogo);

	_isActive = false;
	_isMouseLock = true;
}

// rysuj ekran

int CIntro::iRender(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn = -1;
	int iDelta;

	if (!_isActive)
		Open();

	if (!pMouse->_isPress)
		_isMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	iDelta = ulTimer - _ulTimerStart;

	if (iDelta <= 6000)
	{
		_pCompanyLogo->Render();

		if (iDelta<1000)
		{
			_pBlack->_fAlfa = 1.0f - ((float) iDelta * 0.001f);
			_pBlack->Render();
		}

		if (iDelta>5000)
		{
			iDelta-=5000;
			_pBlack->_fAlfa = ((float) iDelta)*0.001f;
			_pBlack->Render();
		}

	}
	else
	{
		_pGameLogo->Render();

		if (iDelta<=7000)
		{
			iDelta -= 6000;
			_pBlack->_fAlfa = 1.0f- ((float) iDelta * 0.001f);
			_pBlack->Render();
		}

		if (iDelta>12000)
		{
			iDelta-=12000;
			_pBlack->_fAlfa = ((float) iDelta)*0.001f;
			_pBlack->Render();

		}
	}

	if (iDelta>15000)
		return 1;

	return iReturn;
}
