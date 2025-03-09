// krzywe beziera oparte na 4 punkty
//
//    b = new CBezier(0,0,50,50,-200,-300,90,100);
//    
//    for (int i=0; i<=100; i++)
//        printf("# %d : %f %f\n",i,b->fX(i*0.01f),b->fY(i*0.01f));
//    
//    delete b; 

#pragma once

#include <math.h>

class CBezier
{
    
public:
    CBezier();
    CBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    ~CBezier();
    
    float   fX(float v);    // zwraca wartosc X dla przedziału 0.0-1.0
    float   fY(float v);
    
	inline	int iX(float v) { return (int)fX(v); }
	inline	int iY(float v) { return (int)fY(v); }

private:
    
    int     _iX[4], _iY[4]; // zapamietane punkty
    
};

