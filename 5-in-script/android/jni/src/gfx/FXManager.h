// plik z zakodowanymi danymi

#pragma once

#include <stdio.h>
#include <vector>

#include "Particle2DManager.h"
#include "Sprite.h"

#define	FX_SMALL_EXPLOSION			10
#define FX_BIG_EXPLOSION			100

#define FX_SMALL_LOOP				200
#define	FX_BIG_LOOP					300

#define FX_HINT						400

#define FX_SHOW_BOMB				500
#define FX_DIAMOND_EXPLOSION		600
#define FX_RAINBOW_EXPLOSION		800

#define FX_MENU_BUTTON				700

#define FX_LAYER_0					0
#define FX_LAYER_1					1
#define FX_LAYER_2					2
#define FX_LAYER_3					3
#define FX_LAYER_4					4
#define FX_LAYER_5					5
#define FX_LAYER_6					6
#define FX_LAYER_7					7
#define FX_LAYER_8					8
#define FX_LAYER_9					9

class CFXManager
{

public:

	CFXManager();
	~CFXManager();

	int Add(int iType, int x, int y, float r, float g, float b, float a, unsigned long ulTimerStart, unsigned long ulTime);
	int Add(int iType, int x, int y, float r, float g, float b, float a, unsigned long ulTimerStart, unsigned long ulTime, char cLayer);

	void Remove(int id);
	
	void Render(unsigned long ulTimer);
	void Render(unsigned long ulTimer, char cLayer);

	inline char cLayer(int i) { return _cLayer[i]; }
	inline void cLayer(int i, char c) { _cLayer[i] = c; }

private:

	vector <unsigned long>_ulTimerStart;			// kiedy efekt ma siê zacz¹æ
	vector <unsigned long>_ulTimerEnd;				// kiedy efekt ma siê skoñczyæ

	vector <CParticle2DManager*> _pParticles;		// nasze generatory particli

	vector <char>_cLayer;							// warstwy, ¿eby mo¿na by³o ³atwiej kontrolowaæ to co ma siê wyœwietlaæ pod tablic¹ i nad tablic¹

	CSprite		*_pImage[14];

};

