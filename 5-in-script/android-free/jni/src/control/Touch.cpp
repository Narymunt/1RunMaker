#include "Touch.h"

CTouch::CTouch() : _isTouch(false), _iX(0), _iY(0), _iDeltaX(0), _iDeltaY(0), _iStartX(0), _iStartY(0)
{

}

CTouch::~CTouch()
{

}

void CTouch::Update(bool isTouch, int iX, int iY)
{
	if (isTouch)
	{
		SDL_Log("touch x:%d y:%d\n",iX,iY);
		if (!_isTouch)
		{
			_iStartX = iX;
			_iStartY = iY;

			_isTouch = true;
		}
		_iX = iX;
		_iY = iY;

		_iDeltaX = _iX - _iStartX;
		_iDeltaY = _iY - _iStartY;
	}
	else
	{
		_isTouch = false;
	}
}

