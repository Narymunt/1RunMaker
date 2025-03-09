// manager for 2d particles

#include "Particle2DManager.h"
#include <string>
#include <iostream>

// class constructor

CParticle2DManager::CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                                   double fX1, double fY1, double fX2, double fY2, 
                                   double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                                   double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                                   double fAngle, double fMinIncAngle, double fMaxIncAngle,
                                   unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) :
								   _r(1), _g(1), _b(1), _a(1), _isLoop(true)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;
      
    m_ulCount = ulCount;

    m_fX1 = fX1; m_fY1 = fY1; m_fX2 = fX2; m_fY2 = fY2; 
    
    m_fMinIncX = fMinIncX; m_fMinIncY = fMinIncY;
    m_fMaxIncX = fMaxIncX; m_fMaxIncY = fMaxIncY;
    
    m_fAlpha = fAlpha; m_fMinIncAlpha = fMinIncAlpha; m_fMaxIncAlpha = fMaxIncAlpha;
    m_fAngle = fAngle; m_fMinIncAngle = fMinIncAngle; m_fMaxIncAngle = fMaxIncAngle;
    
    m_ulMinLifeTime = ulMinLifeTime; 
	m_ulMaxLifeTime = ulMaxLifeTime;
    
    for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = Randomdouble(m_fX1, m_fX2);
        fY = Randomdouble(m_fY1, m_fY2);

        fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
        fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);
    
        fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
        fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);
    
        ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
    
        m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
    
    m_pImage = new CSprite(cSpriteFilename);
	
}

CParticle2DManager::CParticle2DManager(char cSpriteFilename[], unsigned long ulCount,
                                       double fX1, double fY1, double fX2, double fY2,
                                       double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                                       double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                                       double fAngle, double fMinIncAngle, double fMaxIncAngle,
                                       unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime,
                                       int x1, int y1, int x2, int y2) :
_r(1), _g(1), _b(1), _a(1), _isLoop(true)

{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;
    
    m_ulCount = ulCount;
    
    m_fX1 = fX1; m_fY1 = fY1; m_fX2 = fX2; m_fY2 = fY2;
    
    m_fMinIncX = fMinIncX; m_fMinIncY = fMinIncY;
    m_fMaxIncX = fMaxIncX; m_fMaxIncY = fMaxIncY;
    
    m_fAlpha = fAlpha; m_fMinIncAlpha = fMinIncAlpha; m_fMaxIncAlpha = fMaxIncAlpha;
    m_fAngle = fAngle; m_fMinIncAngle = fMinIncAngle; m_fMaxIncAngle = fMaxIncAngle;
    
    m_ulMinLifeTime = ulMinLifeTime;
	m_ulMaxLifeTime = ulMaxLifeTime;
    
    for (unsigned long i=0; i<ulCount; i++)
    {
        
        fX = Randomdouble(m_fX1, m_fX2);
        fY = Randomdouble(m_fY1, m_fY2);
        
        fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
        fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);
        
        fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
        fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);
        
        ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
        
        m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }
    
    m_pImage = new CSprite(cSpriteFilename, x1, y1, x2, y2);
	
}

// inicjalizowane ze wskaznikiem na istniejacy juz sprite jako particle

CParticle2DManager::CParticle2DManager(CSprite *pImage, unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) :
_r(1), _g(1), _b(1), _a(1), _isLoop(true)
{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	m_ulCount = ulCount;

	m_fX1 = fX1; m_fY1 = fY1; m_fX2 = fX2; m_fY2 = fY2;

	m_fMinIncX = fMinIncX; m_fMinIncY = fMinIncY;
	m_fMaxIncX = fMaxIncX; m_fMaxIncY = fMaxIncY;

	m_fAlpha = fAlpha; m_fMinIncAlpha = fMinIncAlpha; m_fMaxIncAlpha = fMaxIncAlpha;
	m_fAngle = fAngle; m_fMinIncAngle = fMinIncAngle; m_fMaxIncAngle = fMaxIncAngle;

	m_ulMinLifeTime = ulMinLifeTime;
	m_ulMaxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = Randomdouble(m_fX1, m_fX2);
		fY = Randomdouble(m_fY1, m_fY2);

		fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
		fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);

		fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
		fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);

		ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand() % (m_ulMaxLifeTime - m_ulMinLifeTime));

		m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

	m_pImage = pImage;	// przekazujemy wskaznik przez referencje

}

// zmieniamy wszystkie parametry

void CParticle2DManager::Reset(CSprite *pImage, unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) 

{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	m_ulCount = ulCount;

	m_fX1 = fX1; m_fY1 = fY1; m_fX2 = fX2; m_fY2 = fY2;

	m_fMinIncX = fMinIncX; m_fMinIncY = fMinIncY;
	m_fMaxIncX = fMaxIncX; m_fMaxIncY = fMaxIncY;

	m_fAlpha = fAlpha; m_fMinIncAlpha = fMinIncAlpha; m_fMaxIncAlpha = fMaxIncAlpha;
	m_fAngle = fAngle; m_fMinIncAngle = fMinIncAngle; m_fMaxIncAngle = fMaxIncAngle;

	m_ulMinLifeTime = ulMinLifeTime;
	m_ulMaxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = Randomdouble(m_fX1, m_fX2);
		fY = Randomdouble(m_fY1, m_fY2);

		fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
		fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);

		fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
		fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);

		ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand() % (m_ulMaxLifeTime - m_ulMinLifeTime));

		m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

	m_pImage = pImage;

}

// zmianiamy wszystkie parametry poza wskaznikiem na sprite

void CParticle2DManager::Reset(unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime)
{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	m_ulCount = ulCount;

	m_fX1 = fX1; m_fY1 = fY1; m_fX2 = fX2; m_fY2 = fY2;

	m_fMinIncX = fMinIncX; m_fMinIncY = fMinIncY;
	m_fMaxIncX = fMaxIncX; m_fMaxIncY = fMaxIncY;

	m_fAlpha = fAlpha; m_fMinIncAlpha = fMinIncAlpha; m_fMaxIncAlpha = fMaxIncAlpha;
	m_fAngle = fAngle; m_fMinIncAngle = fMinIncAngle; m_fMaxIncAngle = fMaxIncAngle;

	m_ulMinLifeTime = ulMinLifeTime;
	m_ulMaxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = Randomdouble(m_fX1, m_fX2);
		fY = Randomdouble(m_fY1, m_fY2);

		fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
		fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);

		fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
		fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);

		ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand() % (m_ulMaxLifeTime - m_ulMinLifeTime));

		m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

}


// restart particles, generate new positions 

void CParticle2DManager::Restart(unsigned long ulCount)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

	m_pParticles.clear();

	for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = Randomdouble(m_fX1, m_fX2);
        fY = Randomdouble(m_fY1, m_fY2);

        fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
        fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);
    
        fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
        fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);
    
        ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
    
        m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
}

// restart particles, generate new positions

void CParticle2DManager::Restart(void)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

	m_pParticles.clear();

	for (unsigned long i=0; i<m_ulCount; i++)
    {    
  
        fX = Randomdouble(m_fX1, m_fX2);
        fY = Randomdouble(m_fY1, m_fY2);

        fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
        fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);
    
        fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
        fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);
    
        ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
    
        m_pParticles.push_back(new CParticle2D(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
}

// class destructor

CParticle2DManager::~CParticle2DManager()
{
	for (unsigned int i=0; i<m_pParticles.size(); i++)
		delete m_pParticles[i];

	m_pParticles.clear();
    SafeDelete(m_pImage);
}

// regenerate particle if time expired

void CParticle2DManager::Regenerate(unsigned long ulIndex)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

    fX = Randomdouble(m_fX1, m_fX2);
    fY = Randomdouble(m_fY1, m_fY2);
    
    fIncX = Randomdouble(m_fMinIncX, m_fMaxIncX);
    fIncY = Randomdouble(m_fMinIncY, m_fMaxIncY);
    
    fIncAlpha = Randomdouble(m_fMinIncAlpha, m_fMaxIncAlpha);
    fIncAngle = Randomdouble(m_fMinIncAngle, m_fMaxIncAngle);
    
    ulLifeTime = m_ulMinLifeTime + ((unsigned long)rand()%(m_ulMaxLifeTime-m_ulMinLifeTime));
    
    m_pParticles[ulIndex]->Regenerate(fX, fY, m_fAlpha, m_fAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime); 
    
}

// render all particles

int CParticle2DManager::Render(unsigned long ulTimer)
{   
	if (m_pImage == NULL)
		return 0;

	for (unsigned long i=0; i<m_pParticles.size(); i++)
    {
        if (m_pParticles[i]->Update(ulTimer))
        {            
            m_pImage->Position((float)m_pParticles[i]->fGetX(),(float)m_pParticles[i]->fGetY());
			m_pImage->_fRotation= ((float)m_pParticles[i]->fGetAngle());
			m_pImage->_fAlfa = (m_pParticles[i]->fGetAlpha());
			m_pImage->Color(_r, _g, _b);
			m_pImage->RenderC();                             
        }
        else 
        {	
			if (_isLoop)
				Regenerate(i);        
        }
    }    
        
    return 0;   
}

// that should not work, we need to restart vector

void CParticle2DManager::SetCount(unsigned long ulCount)
{
	m_ulCount = ulCount;	
}

// return particles count

unsigned long CParticle2DManager::ulGetCount(void)
{
	return m_ulCount;
}

// return parameters

double CParticle2DManager::dGetX1(void)
{
	return m_fX1;
}

double CParticle2DManager::dGetX2(void)
{
	return m_fX2;
}

double CParticle2DManager::dGetY1(void)
{
	return m_fY1;
}

double CParticle2DManager::dGetY2(void)
{
	return m_fY2;
}

void CParticle2DManager::SetX1(double x1)
{
	m_fX1 = x1;
}

void CParticle2DManager::SetX2(double x2)
{
	m_fX2 = x2;
}

void CParticle2DManager::SetY1(double y1)
{
	m_fY1 = y1;
}

void CParticle2DManager::SetY2(double y2)
{
	m_fY2 = y2;
}

void CParticle2DManager::SetXY12(double x1, double y1, double x2, double y2)
{
	m_fX1 = x1;
	m_fX2 = x2; 
	m_fY1 = y1; 
	m_fY2 = y2;
}

double CParticle2DManager::dGetMinIncX(void)
{
	return m_fMinIncX;
}

double CParticle2DManager::dGetMaxIncX(void)
{
	return m_fMaxIncX;
}

double CParticle2DManager::dGetMinIncY(void)
{
	return m_fMinIncY;
}

double CParticle2DManager::dGetMaxIncY(void)
{
	return m_fMaxIncY;
}

void CParticle2DManager::SetMinIncX(double v)
{
	m_fMinIncX = v; 
}

void CParticle2DManager::SetMinIncY(double v)
{
	m_fMinIncY = v; 
}

void CParticle2DManager::SetMaxIncX(double v)
{
	m_fMaxIncX = v; 
}

void CParticle2DManager::SetMaxIncY(double v)
{
	m_fMaxIncY = v; 
}


void CParticle2DManager::SetInc(double minX, double minY, double maxX, double maxY)
{
	m_fMinIncX = minX; 
	m_fMinIncY = minY;

	m_fMaxIncX = maxX;
	m_fMaxIncY = maxY;
}

double CParticle2DManager::dGetAlpha(void)
{
	return m_fAlpha;
}

double CParticle2DManager::dGetAlphaMin(void)
{
	return m_fMinIncAlpha;
}

double CParticle2DManager::dGetAlphaMax(void)
{
	return m_fMaxIncAlpha;
}

void CParticle2DManager::SetAlpha(double v)
{
	m_fAlpha = v;
}

void CParticle2DManager::SetAlphaMax(double v)
{
	m_fMinIncAlpha = v;
}

void CParticle2DManager::SetAlphaMin(double v)
{
	m_fMaxIncAlpha = v; 
}

void CParticle2DManager::SetAlpha(double alpha, double min, double max)
{
	m_fAlpha = alpha;
	m_fMinIncAlpha = min;
	m_fMaxIncAlpha = max;
}

double CParticle2DManager::dGetAngle(void)
{
	return m_fAngle;
}
	
double CParticle2DManager::dGetAngleMin(void)
{
	return m_fMinIncAngle;
}

double CParticle2DManager::dGetAngleMax(void)
{
	return m_fMaxIncAngle;
}

void CParticle2DManager::SetAngle(double v)
{
	m_fAngle = v;
}

void CParticle2DManager::SetAngleMin(double v)
{
	m_fMinIncAngle = v;
}

void CParticle2DManager::SetAngleMax(double v)
{
	m_fMaxIncAngle = v; 
}

void CParticle2DManager::SetAngle(double angle, double min, double max)
{
	m_fAngle = angle;
	m_fMinIncAngle = min;
	m_fMaxIncAngle = max;
}
	
unsigned long CParticle2DManager::ulGetMinLifeTime(void)
{
	return m_ulMinLifeTime;
}

unsigned long CParticle2DManager::ulGetMaxLifeTime(void)
{
	return m_ulMaxLifeTime;
}

void CParticle2DManager::SetMinLifeTime(unsigned long ulTime)
{
	m_ulMinLifeTime = ulTime;
}

void CParticle2DManager::SetMaxLifeTime(unsigned long ulTime)
{
	m_ulMaxLifeTime = ulTime;
}


double CParticle2DManager::Randomdouble(double a, double b)
{
    return ((b-a)*((double)rand()/RAND_MAX))+a;
}

void CParticle2DManager::Color(float r, float g, float b, float a)
{
	_r = r; 
	_g = g; 
	_b = b; 
	_a = a;
	m_pImage->Color(r, g, b, a);
}

void CParticle2DManager::Color(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;

	m_pImage->Color(r, g, b);
}
