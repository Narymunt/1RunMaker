#include "Bezier.h"

CBezier::CBezier()
{
    _iX[0] = _iY[0] = 0;
    _iX[1] = _iY[1] = 0;
    _iX[2] = _iY[2] = 0;
    _iX[3] = _iY[3] = 0;
    
}

CBezier::CBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    _iX[0] = x1; _iY[0] = y1;
    _iX[1] = x2; _iY[1] = y2;
    _iX[2] = x3; _iY[2] = y3;
    _iX[3] = x4; _iY[3] = y4;
}

CBezier::~CBezier()
{
    
}

float CBezier::fX(float v)
{
    return (pow(1-v,3)*_iX[0]+3*v*pow(1-v,2)*_iX[1]+3*pow(v,2)*(1-v)*_iX[2]+pow(v,3)*_iX[3]);
}

float CBezier::fY(float v)
{
    return (pow(1-v,3)*_iY[0]+3*v*pow(1-v,2)*_iY[1]+3*pow(v,2)*(1-v)*_iY[2]+pow(v,3)*_iY[3]);
}
