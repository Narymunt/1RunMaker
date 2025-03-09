#include "Button.h"

// create 3 bitmap based button

CButton::CButton(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[]) : _x1(0), _y1(0), _x2(0), _y2(0)
{
	Init(pScreen, cImage, cOnOver, cOnClick,0,0,0,0);
}

// create and rescale

CButton::CButton(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[], int x1, int y1, int x2, int y2) : _x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	Init(pScreen, cImage, cOnOver, cOnClick,x1,y1,x2,y2);
}

// utworz przycisk i przesun, bez skali

CButton::CButton(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[], int x1, int y1) : _x1(x1), _y1(y1), _x2(0), _y2(0)
{
	Init(pScreen, cImage, cOnOver, cOnClick,x1,y1,0,0);
}

// create 3 bitmap based button

CButton::CButton(char cImage[], char cOnOver[], char cOnClick[]) : _x1(0), _y1(0), _x2(0), _y2(0)
{
	Init(NULL,  cImage, cOnOver, cOnClick,0,0,0,0);
}

// create and rescale

CButton::CButton(char cImage[], char cOnOver[], char cOnClick[], int x1, int y1, int x2, int y2) : _x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	Init(NULL,  cImage, cOnOver, cOnClick ,x1,y1,x2,y2);
}

// create and rescale

CButton::CButton(char cImage[], char cOnOver[], char cOnClick[], int x1, int y1) : _x1(x1), _y1(y1), _x2(0), _y2(0)
{
	Init(NULL,  cImage, cOnOver, cOnClick ,x1,y1,0,0);
}

// wszystkie nazwy sa wygenerowane

CButton::CButton(CScreen *pScreen, char cName[])
{
	char image[200];
	char over[200];
	char click[200];

	memset(image,0,200);
	memset(over,0,200);
	memset(click,0,200);

	sprintf(image,"%s_image",cName);
	sprintf(over,"%s_over",cName);
	sprintf(click,"%s_click",cName);

	Init(pScreen,image,over,click,0,0,0,0);

}

//=== init

void CButton::Init(CScreen *pScreen, char cImage[], char cOnOver[], char cOnClick[], int x1, int y1, int x2, int y2)
{
	_x1 = x1; _y1 = y1;
	_x2 = x2; _y2 = y2;

	if (pScreen == NULL)
	{
		_pImage = new CSprite(NULL, cImage);
		_pOnOver = new CSprite(NULL, cOnOver);
		_pOnClick = new CSprite(NULL, cOnClick);
	}
	else
	{
		_pImage = new CSprite(pScreen, cImage);
		_pOnOver = new CSprite(pScreen, cOnOver);
		_pOnClick = new CSprite(pScreen, cOnClick);
	}

	if ((x2+y2)==0)
	{
		_pImage->Position(x1,y1);
		_pOnOver->Position(x1,y1);
		_pOnClick->Position(x1,y1);

		_x2 = x1 + _pImage->_fSizeX;
		_y2 = y1 + _pImage->_fSizeY;
	}

	_pImage->Resize(_x1, _y1, _x2, _y2);
	_pOnOver->Resize(_x1, _y1, _x2, _y2);
	_pOnClick->Resize(_x1, _y1, _x2, _y2);
}

// destructor, release graphics 

CButton::~CButton()
{
	SafeDelete(_pImage);
	SafeDelete(_pOnOver);
	SafeDelete(_pOnClick);
}

// check mouse state and draw 

int CButton::Render(CTouch *pTouch)
{
	// check hot coords 

	if ((pTouch->iX()>_x1) && (pTouch->iX()<_x2) && (pTouch->iY()>_y1) && (pTouch->iY()<_y2))
	{
		if (pTouch->_isTouch)
		{
			_pOnClick->Render();
			return ON_LEFT;
		}

		_pOnOver->Render();
		return ON_OVER;
	}

	_pImage->Render();
	return 0;

}

// renderowanie przy uzyciu x i y jako punktow centralnych

int CButton::RenderC(CTouch *pTouch)
{
	int a = (int)(_pImage->_fOriginalX/2);
	int b = (int)(_pImage->_fOriginalY/2);
	int x1 = _x1 - a;
	int	y1 = _y1 - b;
	int x2 = _x2 + a;
	int	y2 = _y2 + b;

	if ((pTouch->iX()>x1) && (pTouch->iX()<x2) && (pTouch->iY()>y1) && (pTouch->iY()<y2))
	{
		if (pTouch->_isTouch)
		{
			_pOnClick->RenderC();
			return ON_LEFT;
		}

		_pOnOver->RenderC();
		return ON_OVER;
	}

	_pImage->RenderC();
	return 0;
}


// setup button position 

void CButton::Position(int x, int y)
{
	_pImage->Position(x,y);
	_pOnOver->Position(x,y);
	_pOnClick->Position(x,y);
}

// set hot coords for button

void CButton::SetHotCoords(int x1, int y1, int x2, int y2)
{
	_x1 = x1; _y1 = y1;
	_x2 = x2; _y2 = y2;

	_pImage->Position(x1,y1);
	_pOnOver->Position(x1,y1);
	_pOnClick->Position(x1,y1);

}

void CButton::Resize(int x1, int y1, int x2, int y2)
{
	_pImage->Resize(x1,y1,x2,y2);
	_pOnOver->Resize(x1,y1,x2,y2);
	_pOnClick->Resize(x1,y1,x2,y2);
}

//=== end ===
