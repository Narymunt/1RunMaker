// main class

#include "Particle2D.h"

// constructor for a single particle

CParticle2D::CParticle2D(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime)
{
    m_fX = fX; 
    m_fY = fY;
    
    m_fAlpha = fAlpha; 
    m_fAngle = fAngle;
    
    m_fIncX = fIncX; 
    m_fIncY = fIncY; 

    m_fIncAngle = fIncAngle;
    m_fIncAlpha = fIncAlpha;
    
    m_ulStartTime =0; 
    
    m_ulLifeTime = ulLifeTime;
    
    m_bActive = false;  
}

// destructor, no pointers to release

CParticle2D::~CParticle2D()
{
}

// regenerate dead particle 

void CParticle2D::Regenerate(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime)
{
    m_fX = fX; 
    m_fY = fY;
    
    m_fAlpha = fAlpha; 
    m_fAngle = fAngle;
    
    m_fIncX = fIncX; 
    m_fIncY = fIncY; 
    
    m_fIncAngle = fIncAngle;
    m_fIncAlpha = fIncAlpha;
    
    m_ulStartTime =0; 
    
    m_ulLifeTime = ulLifeTime;
    
    m_bActive = false;    
    
}

// update particle parameter

int CParticle2D::Update(unsigned long ulTimer)
{
    if (m_ulStartTime == 0)
    {
        m_ulStartTime = ulTimer;
        m_bActive = true;
    }
    
    m_ulTimer = ulTimer - m_ulStartTime;
    
    if (m_ulTimer > m_ulLifeTime) return 0;
    
    if (m_bActive)
    {
        m_fX += m_fIncX; 
        m_fY += m_fIncY; 
        
        m_fAlpha += m_fIncAlpha; 
        
        if (m_fAlpha>1.0f) 
			m_fAlpha=1.0f;
        
		if (m_fAlpha<0.0f) 
			m_fAlpha=0.0f;
        
        m_fAngle += m_fIncAngle;
        
    }    
    
    return 1;   // do nothing 
}

double CParticle2D::fGetX(void)
{
    return m_fX;
}

double CParticle2D::fGetY(void)
{
    return m_fY;
}

double CParticle2D::fGetAlpha(void)
{
    return m_fAlpha;
}

double CParticle2D::fGetIncAlpha(void)
{
    return m_fIncAlpha;
}

double CParticle2D::fGetAngle(void)
{
    return m_fAngle;
}

double CParticle2D::fGetIncAngle(void)
{
    return m_fIncAngle;
}


bool CParticle2D::isActive(void)
{
    return m_bActive;
}