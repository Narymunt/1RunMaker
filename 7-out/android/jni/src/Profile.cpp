// profile graczy

#include "Profile.h"

CProfile::CProfile(char cFilename[])
{
	strcpy(m_cFilename,cFilename);	// zapamietaj nazwe pliku

	for (int i=0; i<8; i++)
	{
		m_ulTotalScore[i] = 0;
		m_ulScore[i] = 0;
		m_ulMap[i] = 0;
		m_ulLevel[i] = 0;

		sprintf(m_cName[i],"_____");
	}

	m_ucCurrentProfile = 0;
}

CProfile::~CProfile()
{

}

void CProfile::SetName(char cNewName[])
{
	strcpy(m_cName[m_ucCurrentProfile],cNewName);	// zapamietaj nazwe gracza
}

char *CProfile::pGetName(void)
{
	return m_cName[m_ucCurrentProfile];
}

void CProfile::SetTotalScore(unsigned long ulScore)
{
	m_ulTotalScore[m_ucCurrentProfile] = ulScore;
}

void CProfile::AddTotalScore(unsigned long ulScore)
{
	m_ulTotalScore[m_ucCurrentProfile] += ulScore;
}

unsigned long CProfile::ulGetTotalScore(void)
{
	return m_ulTotalScore[m_ucCurrentProfile];
}

void CProfile::SetScore(unsigned long ulScore)
{
	m_ulScore[m_ucCurrentProfile] = ulScore;
}

void CProfile::AddScore(unsigned long ulScore)
{
	m_ulScore[m_ucCurrentProfile] += ulScore;
}

unsigned long CProfile::ulGetScore(void)
{
	return m_ulScore[m_ucCurrentProfile];
}

void CProfile::SetLevel(unsigned long ulLevel)
{
	m_ulLevel[m_ucCurrentProfile] = ulLevel;
}

void CProfile::AddLevel(unsigned long ulLevel)
{
	m_ulLevel[m_ucCurrentProfile] += ulLevel;
}

unsigned long CProfile::ulGetLevel(void)
{
	if (m_ulTotalScore[m_ucCurrentProfile] < 10000)
		m_ulLevel[m_ucCurrentProfile] = 1; 

	if (m_ulTotalScore[m_ucCurrentProfile] >=10000 && m_ulTotalScore[m_ucCurrentProfile] < 30000)
		m_ulLevel[m_ucCurrentProfile] = 2;

	if (m_ulTotalScore[m_ucCurrentProfile] >=30000 && m_ulTotalScore[m_ucCurrentProfile] < 60000)
		m_ulLevel[m_ucCurrentProfile] = 3;

	if (m_ulTotalScore[m_ucCurrentProfile] >=60000 && m_ulTotalScore[m_ucCurrentProfile] < 100000)
		m_ulLevel[m_ucCurrentProfile] = 4;

	if (m_ulTotalScore[m_ucCurrentProfile] >=100000 && m_ulTotalScore[m_ucCurrentProfile] < 150000)
		m_ulLevel[m_ucCurrentProfile] = 5;

	if (m_ulTotalScore[m_ucCurrentProfile] >=150000 && m_ulTotalScore[m_ucCurrentProfile] < 210000)
		m_ulLevel[m_ucCurrentProfile] = 6;

	if (m_ulTotalScore[m_ucCurrentProfile] >=210000 && m_ulTotalScore[m_ucCurrentProfile] < 280000)
		m_ulLevel[m_ucCurrentProfile] = 7;

	if (m_ulTotalScore[m_ucCurrentProfile] >=280000 && m_ulTotalScore[m_ucCurrentProfile] < 360000)
		m_ulLevel[m_ucCurrentProfile] = 8;

	if (m_ulTotalScore[m_ucCurrentProfile] >=360000 && m_ulTotalScore[m_ucCurrentProfile] < 450000)
		m_ulLevel[m_ucCurrentProfile] = 9;

	if (m_ulTotalScore[m_ucCurrentProfile] >=450000 && m_ulTotalScore[m_ucCurrentProfile] < 550000)
		m_ulLevel[m_ucCurrentProfile] = 10;

	if (m_ulTotalScore[m_ucCurrentProfile] >=550000 && m_ulTotalScore[m_ucCurrentProfile] < 660000)
		m_ulLevel[m_ucCurrentProfile] = 11;

	if (m_ulTotalScore[m_ucCurrentProfile] >=660000 && m_ulTotalScore[m_ucCurrentProfile] < 780000)
		m_ulLevel[m_ucCurrentProfile] = 12;

	if (m_ulTotalScore[m_ucCurrentProfile] >=780000 && m_ulTotalScore[m_ucCurrentProfile] < 910000)
		m_ulLevel[m_ucCurrentProfile] = 13;

	if (m_ulTotalScore[m_ucCurrentProfile] >=910000 && m_ulTotalScore[m_ucCurrentProfile] < 1050000)
		m_ulLevel[m_ucCurrentProfile] = 14;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1050000 && m_ulTotalScore[m_ucCurrentProfile] < 1200000)
		m_ulLevel[m_ucCurrentProfile] = 15;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1200000 && m_ulTotalScore[m_ucCurrentProfile] < 1360000)
		m_ulLevel[m_ucCurrentProfile] = 16;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1360000 && m_ulTotalScore[m_ucCurrentProfile] < 1530000)
		m_ulLevel[m_ucCurrentProfile] = 17;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1530000 && m_ulTotalScore[m_ucCurrentProfile] < 1720000)
		m_ulLevel[m_ucCurrentProfile] = 18;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1720000 && m_ulTotalScore[m_ucCurrentProfile] < 1910000)
		m_ulLevel[m_ucCurrentProfile] = 19;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1910000 )
		m_ulLevel[m_ucCurrentProfile] = 20;

	return m_ulLevel[m_ucCurrentProfile];
}


float CProfile::fGetProgress(void)
{

	float fProgress;

	if (m_ulTotalScore[m_ucCurrentProfile] < 10000)
	{
		m_ulLevel[m_ucCurrentProfile] = 1; 
		fProgress = (float)(m_ulTotalScore[m_ucCurrentProfile] / 10000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=10000 && m_ulTotalScore[m_ucCurrentProfile] < 30000)
	{
		m_ulLevel[m_ucCurrentProfile] = 2;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-10000) / 20000.0f ) * 100.0f;
	}
	
	if (m_ulTotalScore[m_ucCurrentProfile] >=30000 && m_ulTotalScore[m_ucCurrentProfile] < 60000)
	{
		m_ulLevel[m_ucCurrentProfile] = 3;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-30000) / 30000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=60000 && m_ulTotalScore[m_ucCurrentProfile] < 100000)
	{
		m_ulLevel[m_ucCurrentProfile] = 4;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-60000) / 40000.0f) * 100.0f;		
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=100000 && m_ulTotalScore[m_ucCurrentProfile] < 150000)
	{
		m_ulLevel[m_ucCurrentProfile] = 5;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-100000) / 50000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=150000 && m_ulTotalScore[m_ucCurrentProfile] < 210000)
	{
		m_ulLevel[m_ucCurrentProfile] = 6;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-150000) / 60000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=210000 && m_ulTotalScore[m_ucCurrentProfile] < 280000)
	{
		m_ulLevel[m_ucCurrentProfile] = 7;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-210000) / 70000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=280000 && m_ulTotalScore[m_ucCurrentProfile] < 360000)
	{
		m_ulLevel[m_ucCurrentProfile] = 8;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-280000) / 80000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=360000 && m_ulTotalScore[m_ucCurrentProfile] < 450000)
	{
		m_ulLevel[m_ucCurrentProfile] = 9;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-360000) / 90000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=450000 && m_ulTotalScore[m_ucCurrentProfile] < 550000)
	{
		m_ulLevel[m_ucCurrentProfile] = 10;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-450000) / 100000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=550000 && m_ulTotalScore[m_ucCurrentProfile] < 660000)
	{
		m_ulLevel[m_ucCurrentProfile] = 11;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-550000) / 110000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=660000 && m_ulTotalScore[m_ucCurrentProfile] < 780000)
	{
		m_ulLevel[m_ucCurrentProfile] = 12;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-660000) / 120000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=780000 && m_ulTotalScore[m_ucCurrentProfile] < 910000)
	{
		m_ulLevel[m_ucCurrentProfile] = 13;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-780000) / 130000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=910000 && m_ulTotalScore[m_ucCurrentProfile] < 1050000)
	{
		m_ulLevel[m_ucCurrentProfile] = 14;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-910000) / 140000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1050000 && m_ulTotalScore[m_ucCurrentProfile] < 1200000)
	{
		m_ulLevel[m_ucCurrentProfile] = 15;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1050000) / 150000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1200000 && m_ulTotalScore[m_ucCurrentProfile] < 1360000)
	{
		m_ulLevel[m_ucCurrentProfile] = 16;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1200000) / 160000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1360000 && m_ulTotalScore[m_ucCurrentProfile] < 1530000)
	{
		m_ulLevel[m_ucCurrentProfile] = 17;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1360000) / 170000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1530000 && m_ulTotalScore[m_ucCurrentProfile] < 1720000)
	{
		m_ulLevel[m_ucCurrentProfile] = 18;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1530000) / 180000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1720000 && m_ulTotalScore[m_ucCurrentProfile] < 1910000)
	{
		m_ulLevel[m_ucCurrentProfile] = 19;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1720000) / 190000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1910000 )
	{
		m_ulLevel[m_ucCurrentProfile] = 20;
		fProgress = 100.0f;
	}

	return fProgress;
}

// zapis profilu

bool CProfile::bSave(void)
{
	FILE	*plik;

	if ((plik=fopen(m_cFilename,"wb"))==NULL)
	{
		return false;
	}
	else
	{
		fprintf(plik,"%d\n",m_ucCurrentProfile);

		for (int i=0; i<8; i++)
		{
			fprintf(plik,"%s\n%d\n%d\n%d\n%d\n", m_cName[i],(unsigned int) m_ulTotalScore[i],(unsigned int) m_ulScore[i],(unsigned int) m_ulMap[i],(unsigned int) m_ulLevel[i]);

			for (int j=0; j<21;j++)
				fprintf(plik,"%d\n",(unsigned int)m_ucTroophy[i][j]);
		}
	}
	
	fclose(plik);

	return true;
}

bool CProfile::bLoad(void)
{
	FILE	*plik;

	plik = NULL;

	if ((plik=fopen(m_cFilename,"rt"))==NULL)
	{
		return false;
	}
	else
	{
		fscanf(plik,"%d\n",&m_ucCurrentProfile);

		for (int i=0; i!=8; i++)
		{
			fscanf(plik,"%s\n%d\n%d\n%d\n%d\n", m_cName[i], &m_ulTotalScore[i], &m_ulScore[i], &m_ulMap[i], &m_ulLevel[i]);

			for (int j=0; j!=21; j++)
				fscanf(plik,"%d\n",&m_ucTroophy[i][j]);
		}
	}

	fclose(plik);

	// poprawka dla etapu, jezeli ktos ma etap 0 lub > 10 to zamieniamy na 1

	for (int i=0; i<8; i++)
	{
		if (m_ulLevel[i]>9 || m_ulLevel[i]<1)
			m_ulLevel[i] = 1;
	}

	return true;
}

void CProfile::ucTroophy(int iIndex, unsigned char ucValue)
{
	m_ucTroophy[m_ucCurrentProfile][iIndex] = ucValue;
}

unsigned char CProfile::ucTroophy(int iIndex)
{
	return m_ucTroophy[m_ucCurrentProfile][iIndex];
}

//=== mapa oznacza poziom / miejsce na mapie, ktore wybieramy w eLevelMenu

void CProfile::ulMap(unsigned long ul)
{
	m_ulMap[m_ucCurrentProfile] = ul;
}

unsigned long CProfile::ulMap(void)
{
	return m_ulMap[m_ucCurrentProfile];
}

void CProfile::ucCurrentProfile(unsigned char ucProfile)	// ktory profil jest aktualnie u¿ywany
{
	m_ucCurrentProfile = ucProfile;
}

unsigned char CProfile::ucCurrentProfile(void)
{
	return m_ucCurrentProfile;
}

int CProfile::iNameSize(void)
{
	return strlen(m_cName[m_ucCurrentProfile]);
}

