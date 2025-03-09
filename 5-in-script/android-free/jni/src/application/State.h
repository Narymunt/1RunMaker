// State - stan aplikacji (aktualnie otwarty ekran/okno)

#pragma once

#include "../gfx/Screen.h"
#include "../control/Touch.h"

class CState
{

public:

	CState();
	~CState();

	void				isActive(bool bState);		// are data loaded ? 
	bool				isActive(void);				// return flag

	virtual void		Open(void);			// load
	virtual void		Close(void);		// unload

	virtual int			iRender(unsigned long ulTimer, CTouch *pTouch);

	inline void			isMouseLock(bool b) { _isMouseLock = b; }
	inline bool			isMouseLock(void) { return _isMouseLock; }

//	int		Render(unsigned long ulTimer,CMouse *pMouse);		// rysuje pojedyncza klatke

protected:

	bool				_isActive;			// data loaded or not ? 
	bool				_isMouseLock;		// czy myszka jest zablokowana po poprzednim ekranie ? 

	CScreen				*_pScreen;			// zapamietujemy w niektorych metodach

	unsigned long		_ulTimerStart;

};

