#pragma once

// do trzymania fontow jako grafiki, gdzie kazda litera to osobny sprite
// tylko duze literki

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "../Main.h"
#include "Sprite.h"

class CSpriteFont
{

	public : 
	
		CSpriteFont();
		~CSpriteFont();
		
		void Print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[]);		
		
		int	iSize(float fSizeX, char cText[]);	// zwraca ile szerokoœci bêdzie zajmowaæ dany napis

	private:
	
		CSprite		*m_pCharTable[37];
	
};

