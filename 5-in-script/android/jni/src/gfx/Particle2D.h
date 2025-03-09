// particle2d class contain informations about single particle

#pragma once

#include <time.h>

class CParticle2D
{
	
public: 
	
    CParticle2D(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime);
    ~CParticle2D();            
    
    void Regenerate(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime);  

    int Update(unsigned long ulTimer);       // update parameters
    
    double fGetX(void);
    double fGetY(void);
    
    double fGetAlpha(void);
    double fGetIncAlpha(void);
    
    double fGetAngle(void);
    double fGetIncAngle(void);
    
    bool isActive(void);
    
private:	
    
    double           m_fX, m_fY;
    double           m_fAlpha, m_fAngle;
    
    double           m_fIncAlpha, m_fIncAngle;    

    double           m_fIncX, m_fIncY;
    
    
    unsigned long   m_ulTimer;  // current timer 

    unsigned long   m_ulStartTime;  // rendering start timer 
    unsigned long   m_ulLifeTime;   
    
    bool			m_bActive;            
	
};

