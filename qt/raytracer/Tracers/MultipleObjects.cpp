#include "MultipleObjects.h"
#include "World/World.h"

//// -------------------------------------------------------------------- default constructor

MultipleObjects::MultipleObjects()
    : Tracer()
{}


//// -------------------------------------------------------------------- constructor

MultipleObjects::MultipleObjects(World* _worldPtr)
    : Tracer(_worldPtr)
{}


//// -------------------------------------------------------------------- destructor

MultipleObjects::~MultipleObjects() {}


//// -------------------------------------------------------------------- trace_ray

RGBColor
MultipleObjects::trace_ray(const Ray& ray) const {
    ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed

       return sr.hit_an_object ? sr.color : world_ptr->background_color;
}

