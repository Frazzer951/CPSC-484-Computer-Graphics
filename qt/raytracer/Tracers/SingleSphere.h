#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__

#include "Tracer.h"


//=====================================
// SingleSphere
//=====================================
//
class SingleSphere: public Tracer {
public:
    SingleSphere();
    SingleSphere(World* _worldPtr) ;

    virtual ~SingleSphere();


    virtual RGBColor trace_ray(const Ray& ) const;
};

#endif
