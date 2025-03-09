// Animacja to stos klatek animacji, nie powtarzaj¹cych siê
// dopiero event okresla ktore klatki z animacji nalezy odtwarzac
// po module dziedziczymy isActive

#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include "../Main.h"
#include "../GameObject.h"
#include "Sprite.h"
#include "Screen.h"

class CAnimation : public CGameObject
{
	public:
		CAnimation(char cFile[], int iFrameCount, char cExt[]);		// dodaje animacje plikXXX.ext, klatki liczone sa od 0
		~CAnimation();
	
		void	iFrameCount(int iFrameCount);
		int		iFrameCount(void);	

		void	AddFrame(char cFilename[]);

		void	Open();								// wczytaj dane
		void	Close(void);						// usun dane

		void	Render(int iFrame);
		void	Render(int iFrame, int iX, int iY);
		void	Render(int iFrame, int iX, int iY, unsigned char alfa);	
		void	Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY);
		void	Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation);
		void	Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation, float fRotationX, float fRotationY);
		
	private:
		
		char	m_cFile[200];
		int		m_iFrameCount;
		char	m_cExt[3];

		std::vector <CSprite*>	m_pSprite;		// tutaj nasze bitmapy
};
