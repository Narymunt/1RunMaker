#include "State.h"

//=== onstruktor

CState::CState()
{
	_isActive = false;		// data not loaded
	_isMouseLock = true;
	_pScreen = NULL;
	_ulTimerStart = 0;
}

//=== destructor 

CState::~CState()
{
	_isActive = false;
	_pScreen = NULL;
}

//=== set flag

void CState::isActive(bool bState)
{
	_isActive = bState;
}

//=== return flag

bool CState::isActive(void)
{
	return _isActive;
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

int CState::iRender(unsigned long ulTimer, CTouch *pTouch)
{
	return 0;
}
