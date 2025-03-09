
#include "Mouse.h"

// constructor

CMouse::CMouse() :
_isPress(false), _iMouseX(0), _iMouseY(0), _iStartX(0), _iStartY(0), _iEndX(0), _iEndY(0)
{

}

// class destructor

CMouse::~CMouse()
{
}

// update

void CMouse::Update(int x, int y, bool b)
{
    if (b==true)
    {
        if (_isPress)
        {
            _iEndX = _iMouseX = x;
            _iEndY = _iMouseY = y;
        }
        else
        {
            _iStartX = _iMouseX = x;
            _iStartY = _iMouseY = y;
            _isPress = true;
        }
    }
    else
    {
        _iMouseX = x;
        _iMouseY = y;
        
        _isPress = false;
    }
}

void CMouse::Reset()
{
    _isPress = false;
    _iMouseX = _iStartX = _iEndX = 0;
    _iMouseY = _iStartY = _iEndY = 0;
}

// end

