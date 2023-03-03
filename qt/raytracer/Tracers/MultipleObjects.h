#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"


//=====================================
// MultipleObjects
//=====================================
//
class MultipleObjects: public Tracer {
public:
    MultipleObjects();
    MultipleObjects(World* _world_ptr);

    virtual	~MultipleObjects();


    virtual RGBColor trace_ray(const Ray& ray) const;
};

#endif

