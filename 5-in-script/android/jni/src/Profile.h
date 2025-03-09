// profile - profil gracza 
// zawiera w srodku profile dla 8 uzytkownikow / graczy

#pragma once

#include <stdio.h>
#include "AndroidFile.h"

class CProfile  
{

public:

	CProfile(char cFilename[]);
	~CProfile();

	void	SetName(char cNewName[]);
	char	*pGetName(void);
	int		iNameSize(void);


	void	SetTotalScore(unsigned long ulScore);
	void	AddTotalScore(unsigned long ulScore);
	unsigned long ulGetTotalScore(void);

	void	SetScore(unsigned long ulScore);
	void	AddScore(unsigned long ulScore);
	unsigned long ulGetScore(void);

	void	SetLevel(unsigned long ulLevel);
	void	AddLevel(unsigned long ulLevel);
	unsigned long ulGetLevel(void);

	void	ulMap(unsigned long ul);	
	unsigned long ulMap(void);

	bool	bSave(void);		// save profile
	bool	bLoad(void);

	float	fGetProgress(void);	// zwraca procentowo ile jeszcze nam brakuje do konca levelu

	void	ucTroophy(int iIndex, unsigned char ucValue);
	unsigned char ucTroophy(int iIndex); 

	void	ucCurrentProfile(unsigned char ucProfile);	// ktory profil jest aktualnie u¿ywany
	unsigned char ucCurrentProfile(void);

private:

	char	m_cFilename[1024];	// nazwa pliku z danymi profilu
	char	m_cName[8][100];	// nazwa profilu

	unsigned char	m_ucCurrentProfile;	

	unsigned long	m_ulTotalScore[8];	// suma wszystkich zebranych punktow
	unsigned long	m_ulScore[8];		// aktualna suma punktow
	unsigned long	m_ulMap[8];			// ktore mapy sa dostepne, numer oznacza mapa1, mapa2 itd. 
	unsigned long	m_ulLevel[8];		// aktualny poziom w danym levelu, dla kazdego gracza/profilu, ktore sa dostepne

	unsigned char	m_ucTroophy[9][21];	// zdobyte osiagniecia

};

