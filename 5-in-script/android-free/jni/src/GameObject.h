// game object - general object class

#pragma once

#include "gfx/Screen.h"

class CGameObject
{

public:

	CGameObject();
	~CGameObject();

	void				Open(void);			// load 
	void				Close(void);		// unload

    bool				_isActive;			// data loaded or not ?
    bool				_isMouseLock;		// czy myszka jest zablokowana po poprzednim ekranie ?
    CScreen				*_pScreen;			// zapamietujemy w niektorych metodach

};

