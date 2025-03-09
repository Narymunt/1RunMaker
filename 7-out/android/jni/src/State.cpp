#include "State.h"

//=== onstruktor

CState::CState() :
_isActive(false), _isMouseLock(true), _pScreen(0), _ulTimerStart(0)
{
}

//=== destructor 

CState::~CState()
{
	_isActive = false;
	_pScreen = NULL;
}

//=== load and prepare data

void CState::Open(void)
{
	_isActive = true;
	_isMouseLock = true;
}

//=== release data

void CState::Close(void)
{
	_isActive = false;
	_isMouseLock = true;
	_pScreen = NULL;
}

// rysuj ekran

int CState::iRender(unsigned long ulTimer, CMouse *pMouse)
{
	return 0;
}
