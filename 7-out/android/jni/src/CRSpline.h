// catmull rom spline
// w przeciwienstwie do beziera mozna dodac nieograniczona liczbe punktow
// CRSpline *cr;
// Vec3 v3;
//    cr = new CRSpline();
//    cr->AddPoint(Vec3(0,0,0));
//    cr->AddPoint(Vec3(-10,-20,-30));
//    cr->AddPoint(Vec3(30,20,10));
//    cr->AddPoint(Vec3(100,100,100));   
//    for (int i=0; i<=1000; i++)
//    {
//        v3 = cr->GetPoint(i*0.001f);
//        printf("# %d : %.2f %.2f %.2f\n",i,v3.x,v3.y,v3.z);
//    }  
//    delete cr;  

#pragma once

#include "Vec3.h"
#include <vector>

class CRSpline
{
public:

    CRSpline();
    CRSpline(const CRSpline&);
    ~CRSpline();

    // Operations
   
    void            AddPoint(const Vec3 &v);
	
    Vec3        GetPoint(float t);   // t = 0...1; 0=vp[0] ... 1=vp[max]
	
    int             GetNumPoints(void);
	Vec3        &GetNthPoint(int n);

    // Static method for computing the Catmull-Rom parametric equation
    // given a time (t) and a vector quadruple (p1,p2,p3,p4).
    
    static Vec3 Eq(float t, const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, const Vec3 &p4);

private:
    
    std::vector<Vec3> vp;
    float delta_t;

};
