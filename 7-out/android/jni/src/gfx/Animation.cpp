#include "Animation.h"

#pragma warning(disable : 4996)	// sprintf unsafe

//=== inicjalizacja, nie wczytujemy jeszcze danych

CAnimation::CAnimation(char cFile[], int iFrameCount, char cExt[]) :
m_iFrameCount(iFrameCount)
{
	strcpy(m_cFile,cFile);	// zapamietujemy nazwe pliku i rozszerzenie
	strcpy(m_cExt,cExt);
}

//=== destruktor, kasowanie danych

CAnimation::~CAnimation()
{
	Close();
}

//=== inicjalizacja, wczytanie danych

void CAnimation::Open()
{
	char cBuffer[256];	// tutaj wygenerujemy nazwe pliku

	for (int i=0; i<m_iFrameCount; i++)
	{
		if (m_iFrameCount>99) // jezeli klatek jest minimum 100 to stosujemy 3-cyfrowa numeracje
		{
			if (i<10)
				sprintf(cBuffer,"%s00%d.%s",m_cFile,i,m_cExt);

			if (i>9 && i <100)
				sprintf(cBuffer,"%s0%d.%s",m_cFile,i,m_cExt);

			if (i>99)
				sprintf(cBuffer,"%s%d.%s",m_cFile,i,m_cExt);
		}

		if (m_iFrameCount<100) // jezeli klatek jest mniej ni¿ 100 to stosujemy 3-cyfrowa numeracje
		{
			if (i<10)
				sprintf(cBuffer,"%s0%d.%s",m_cFile,i,m_cExt);

			if (i>9 && i <100)
				sprintf(cBuffer,"%s%d.%s",m_cFile,i,m_cExt);
		}
		m_pSprite.push_back(new CSprite(cBuffer));
	}
	_isActive = true;
}

//=== skasuj nie uzywane dane

void CAnimation::Close(void)
{
	for (unsigned int i=0; i<m_pSprite.size(); i++)
		delete m_pSprite[i];

	m_pSprite.clear();

	_isActive = false;
}

//=== przycina liczbe klatek poprzez ustawienie liczby na mniejsza niz jest w rzeczywistosci

void CAnimation::iFrameCount(int iFrameCount)
{
	m_iFrameCount = iFrameCount;
}

//=== zwraca liczbe klatek 

int CAnimation::iFrameCount(void)
{
	return m_iFrameCount;
}

//=== dodajemy klatke na koniec kolejki

void CAnimation::AddFrame(char cFilename[])
{
	m_pSprite.push_back(new CSprite(cFilename));
}

//=== renderuj klatke o podanym numerze

void CAnimation::Render(int iFrame)
{
	if (iFrame>=0 && iFrame < m_iFrameCount)
		m_pSprite[iFrame]->Render();
}

void CAnimation::Render(int iFrame, int iX, int iY)
{
	if (iFrame>=0 && iFrame<m_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Render();
	}
}

void CAnimation::Render(int iFrame, int iX, int iY, unsigned char alfa)
{
	if (iFrame>=0 && iFrame<m_iFrameCount)
	{
		m_pSprite[iFrame]->_fAlfa=alfa;
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Render();
	}
}


void CAnimation::Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY)
{
	if (iFrame>=0 && iFrame<m_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Scale(fScaleX, fScaleY);
		m_pSprite[iFrame]->Render();
	}
}

void CAnimation::Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation)
{
	if (iFrame>=0 && iFrame<m_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Scale(fScaleX, fScaleY);
		m_pSprite[iFrame]->_fRotation= fRotation;
		m_pSprite[iFrame]->Render();
	}
}

void CAnimation::Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation, float fRotationX, float fRotationY)
{
	if (iFrame>=0 && iFrame<m_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Scale(fScaleX, fScaleY);
		m_pSprite[iFrame]->_fRotation = fRotation;
		m_pSprite[iFrame]->RenderC();
	}
}

