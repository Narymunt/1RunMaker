#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CTGA
{

public:

	CTGA(char f[]);
	CTGA(unsigned long x, unsigned long y);

	~CTGA();

	bool isFit(unsigned long x, unsigned long y);	// czy obrazek miesci sie w tych wymiarach
	bool isSpriteFit(unsigned long x, unsigned long y);	// czy sprite miesci sie w tych wymiarach

	void resize(double f);			// zmiana rozmiaru obrazu
	void resizeSprite(double f);	// zmiana rozmiaru sprite

	void resize(double fx, double fy); // zmiana rozmiaru obrazu
	void resizeSprite(double fx, double fy); // zmiara rozmiaru sprite

	void resizeTo(unsigned long nx, unsigned long ny);	// przeskaluj obraz do wymiaru
	void resizeSpriteTo(unsigned long nx, unsigned long ny);

	void save(char f[]);
	void saveSprite(char f[]);

	void renderSprite(unsigned char *buffer, unsigned long sizeX, unsigned long sizeY);
	void renderSprite(unsigned long X, unsigned long Y, unsigned char *buffer, unsigned long sizeX, unsigned long sizeY);		// renderuj od okreslonego punktu

	void renderChannel(unsigned char *buffer, unsigned long sizeX, unsigned long sizeY); // kolor 0 pomijamy

	void cleanAlfa();	// wyczyœæ obraz ze œmieci alfa
	void clip();		// wyodrêbnij sprite z obrazu

	void setA(unsigned char a);	// alfa = a dla ka¿dego pixela
	void setA(unsigned char a, unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2); 

	void flipV();	// zamienia do góry nogami

	void dark(unsigned char l);		// zrob ciemniejszy obraz
	void light(unsigned char l);	// zrob jasniejszy obraz
	void grey(unsigned char l); // usrednij kolory
	void blur(unsigned char l); // usrednij kolory

	void darkSprite(unsigned char l);		// zrob ciemniejszy obraz
	void lightSprite(unsigned char l);	// zrob jasniejszy obraz
	void greySprite(); // usrednij kolory
	void blurSprite();



	unsigned char _header[18];			

	unsigned int _sizeX;
	unsigned int _sizeY;
	unsigned int _centerX, _centerY;
	unsigned char _bpp;
	unsigned long _size;

	unsigned char *_buffer;
	
	unsigned char *_sprite;
	unsigned long _x1, _x2, _y1, _y2;	// clipping dla sprite, który znajduje siê w obrazie
	unsigned long _spriteSize;
	unsigned long _spriteSizeX, _spriteSizeY;
	unsigned int _spriteCenterX, _spriteCenterY;

};