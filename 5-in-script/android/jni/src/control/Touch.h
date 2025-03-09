#pragma once

// touch screen

#include "../Main.h"
#include "../gfx/Sprite.h"

class CTouch
{

public:
	CTouch();
	~CTouch();

	void Update(bool isTouch, int iX, int iY);

	inline int	iStartX(void) { return _iStartX; }
	inline void iStartX(int i) { _iStartX = i; }

	inline int	iStartY(void) { return _iStartY; }
	inline void iStartY(int i) { _iStartY = i; }

	inline void iTouchX(int iX) { _iX = iX; }
	inline void iTouchY(int iY) { _iY = iY; }

	inline int iTouchX(void) { return _iX; }
	inline int iTouchY(void) { return _iY; }

	inline int iDeltaX(void) { return _iDeltaX; }
	inline int iDeltaY(void) { return _iDeltaY; }

	inline int iX(void) { return _iX; }
	inline int iY(void) { return _iY; }

	bool	_isTouch;
	int		_iStartX, _iStartY, _iX, _iY, _iDeltaX, _iDeltaY;

};


