// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef __TRACER__
#define __TRACER__

#include "Utilities/Constants.h"
#include "Utilities/Ray.h"
#include "Utilities/RGBColor.h"

struct World;


//=====================================
// Tracer
//=====================================
//
class Tracer {
public:
    Tracer() = default;
    Tracer(World* _world_ptr) : world_ptr(_world_ptr) { }

    virtual ~Tracer() {
        if (world_ptr != NULL) { world_ptr = NULL; }
    }


    virtual RGBColor trace_ray(const Ray&)           const { return black; }
    virtual RGBColor trace_ray(const Ray, const int) const {  return black; }  // depth ignored

protected:
    World* world_ptr;
};

#endif
