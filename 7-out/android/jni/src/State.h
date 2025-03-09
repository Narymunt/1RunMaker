// State - stan aplikacji (aktualnie otwarty ekran/okno)

#pragma once

#include "Screen.h"
#include "Mouse.h"

class CState
{

public:

	CState();
	~CState();

	virtual void		Open(void);			// load
	virtual void		Close(void);		// unload

	virtual int			iRender(unsigned long ulTimer, CMouse *pMouse);

	bool				_isActive;			// data loaded or not ? 
	bool				_isMouseLock;		// czy myszka jest zablokowana po poprzednim ekranie ? 

	CScreen				*_pScreen;			// zapamietujemy w niektorych metodach

	unsigned long		_ulTimerStart;

};

