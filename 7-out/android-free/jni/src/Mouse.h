// mouse handle class

#pragma once

#include "iGame.h"
#include "GameObject.h"

class CMouse : public CGameObject
{

public:
	CMouse();
	~CMouse();

    void    Update(int x, int y, bool b);
    void    Reset();
    
    bool    _isPress;

    int     _iMouseX;		// cursor positions
    int     _iMouseY;
    
    int     _iStartX, _iStartY;     // poczatek naciskania
    int     _iEndX, _iEndY;         // koniec naciskania
        
};


