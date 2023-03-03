#ifndef __RAY_CAST__
#define __RAY_CAST__

#include "Tracer.h"


//=====================================
// RayCast
//=====================================
//
class RayCast: public Tracer {
public:
    RayCast();
    RayCast(World* _worldPtr);

    virtual ~RayCast();


    virtual RGBColor trace_ray(const Ray&) const;   // ignore depth
    virtual RGBColor trace_ray(const Ray, const int) const;
};

#endif






