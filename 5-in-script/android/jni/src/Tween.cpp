#include "Tween.h"

CTween::CTween()
{
    
}

CTween::CTween(int iSize)
{
    for (int i=0; i<iSize; ++i)
        _pTable.push_back(0);
    
}

CTween::CTween(float fv1, float fv2, int i)
{
    _fV1 = fv1; _fV2 = fv2;

    for (int j=0; j<i; j++)
        _pTable.push_back(0);
}

CTween::CTween(float fv1, float fv2, float f)
{
    float step, fstart;

    _fV1 = fv1; _fV2 = fv2;
   
    step = float((fv2-fv1)/f);

    fstart = fv1;
    
    while (fstart!=fv2)
    {
        _pTable.push_back(0);
        fstart += step;
    }
    
}

CTween::CTween(float fv1, float fv2)
{
    _fV1 = fv1; _fV2 = fv2;
}

CTween::~CTween()
{
    _pTable.clear();
}

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float CTween::fBack(float t)
{
    float fValue;
    float s = 1.70158f;
    fValue =  t * t * ( (s+1) * t - s);
    return _fV1+((_fV2 - _fV1)*fValue);
}

float CTween::fBack(float f1, float f2, float t)
{
    float fValue;
    float s = 1.70158f;
    
    _fV1 = f1; _fV2 = f2;
    
    fValue =  t * t * ( (s+1) * t - s);
    return _fV1+((_fV2 - _fV1)*fValue);
}


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float CTween::fBounce( float t )
{
    const float v = 1 - t;
    float fValue,c,d;
    
    if ( v < (1 / 2.75) )
    {
        c = v;
        d = 0;
    }
    else if ( v < (2 / 2.75) )
    {
        c = v - 1.5 / 2.75;
        d = 0.75;
    }
    else if ( v < (2.5 / 2.75) )
    {
        c = v - 2.25 / 2.75;
        d = 0.9375;
    }
    else
    {
        c = v - 2.625 / 2.75;
        d = 0.984375;
    }
    
    fValue = 1 - (7.5625 * c * c + d);

    return _fV1+((_fV2 - _fV1)*fValue);
}

float CTween::fBounce( float f1, float f2, float t )
{
    const float v = 1 - t;
    float fValue,c,d;

    _fV1 = f1; _fV2 = f2;    
    
    if ( v < (1 / 2.75) )
    {
        c = v;
        d = 0;
    }
    else if ( v < (2 / 2.75) )
    {
        c = v - 1.5 / 2.75;
        d = 0.75;
    }
    else if ( v < (2.5 / 2.75) )
    {
        c = v - 2.25 / 2.75;
        d = 0.9375;
    }
    else
    {
        c = v - 2.625 / 2.75;
        d = 0.984375;
    }
    
    fValue = 1 - (7.5625 * c * c + d);
    
    return _fV1+((_fV2 - _fV1)*fValue);
}

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float CTween::fCirc( float t )
{
    float fValue = 1 - sqrt(1 - t * t);
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_circ_func()

float CTween::fCirc( float f1, float f2, float t )
{
    float fValue = 1 - sqrt(1 - t * t);
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*fValue);    
} // easing_circ_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float CTween::fCubic( float t )
{
    float fValue = t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_cubic_func()

float CTween::fCubic( float f1, float f2, float t )
{
    float fValue = t * t * t;
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_cubic_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float CTween::fElastic( float t )
{
    const float pi(3.1415927);
    float v(t-1);
    const float p(0.3);
    
    float fValue = -pow(2, 10 * v) * sin( (v - p / 4) * 2 * pi / p );
    return _fV1+((_fV2 - _fV1)*fValue);

} // easing_elastic_func()

float CTween::fElastic( float f1, float f2, float t )
{
    const float pi(3.1415927);
    float v(t-1);
    const float p(0.3);

    _fV1 = f1; _fV2 = f2;
    
    float fValue = -pow(2, 10 * v) * sin( (v - p / 4) * 2 * pi / p );
    return _fV1+((_fV2 - _fV1)*fValue);
    
} // easing_elastic_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float CTween::fExpo( float t )
{
    float fValue = t == 0 ? 0 : pow(2, 10 * (t - 1));
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_expo_func()

float CTween::fExpo( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue = t == 0 ? 0 : pow(2, 10 * (t - 1));
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_expo_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float CTween::fLinear( float t )
{
    return _fV1+((_fV2 - _fV1)*t);
} // easing_linear_func()

float CTween::fLinear( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*t);
} // easing_linear_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float CTween::fQuad( float t )
{
    float fValue =  t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quad_func()

float CTween::fQuad( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue =  t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quad_func()

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float CTween::fQuart( float t )
{
    float fValue = t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quart_func()

float CTween::fQuart( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue = t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quart_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float CTween::fQuint( float t )
{
    float fValue = t * t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quint_func()

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float CTween::fQuint( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue = t * t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quint_func()

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float CTween::fSine( float t )
{
    const float pi(3.1415927);
    float fValue = 1 - cos(t * pi / 2);
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_sine_func()

float CTween::fSine( float f1, float f2, float t )
{
    const float pi( 3.1415927 );
    float fValue = 1 - cos(t * pi / 2);
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_sine_func()




