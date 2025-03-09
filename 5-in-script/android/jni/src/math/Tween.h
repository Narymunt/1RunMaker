#pragma once

#include <math.h>
#include <vector>

class CTween
{
    
public:
    
    CTween();
    CTween(int iSize);                      // tutaj tworzymy na starcie tablice o wskazanym rozmiarze
    CTween(float fv1, float fv2, int i);    // podajemy dwie wartości i ilość elementów, które chcemy mieć w tablicy
    CTween(float fv1, float fv2, float f);  // automatycznie tworzy tablice o rozmiarze potrzebnym dla danych wartosci
    CTween(float fv1, float fv2);           // podajemy dwie wartości, nie tworzymy tablicy
    ~CTween();
    
    float       fBack(float t);
    float       fBack(float f1, float f2, float t);
    
    float       fBounce(float t);
    float       fBounce(float f1, float f2, float t);
    
    float       fCirc(float t);
    float       fCirc(float f1, float f2, float t);
    
    float       fCubic(float t);
    float       fCubic(float f1, float f2, float t);
    
    float       fElastic(float t);
    float       fElastic(float f1, float f2, float t);
    
    float       fExpo(float t);
    float       fExpo(float f1, float f2, float t);
    
    float       fLinear(float t);
    float       fLinear(float f1, float f2, float t);
    
    float       fQuad(float t);
    float       fQuad(float f1, float f2, float t);
    
    float       fQuart(float t);
    float       fQuart(float f1, float f2, float t);
    
    float       fQuint(float t);
    float       fQuint(float f1, float f2, float t);
    
    float       fSine(float t);
    float       fSine(float f1, float f2, float t);
    
private:
    
    float                   _fV1, _fV2;     // nasze dwa punkty, wartości pomiędzy którymi się poruszamy
    std::vector <float>     _pTable;        // tablica z wartościami, nie zawsze używana
    
    
};
