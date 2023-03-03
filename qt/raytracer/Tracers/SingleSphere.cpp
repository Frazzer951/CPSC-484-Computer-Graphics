#include "SingleSphere.h"
#include "Utilities/ShadeRec.h"
#include "World/World.h"


//// -------------------------------------------------------------------- default constructor

SingleSphere::SingleSphere()
    : Tracer()
{}


// -------------------------------------------------------------------- constructor
		
SingleSphere::SingleSphere(World* _worldPtr)
    : Tracer(_worldPtr)
{}


//// -------------------------------------------------------------------- destructor

SingleSphere::~SingleSphere() {}


// -------------------------------------------------------------------- trace_ray

RGBColor
SingleSphere::trace_ray(const Ray& ray) const {
    ShadeRec	sr(*world_ptr); 	// not used
    double    	t;  				// not used
	
    return world_ptr->sphere.hit(ray, t, sr) ? red : black;
}


