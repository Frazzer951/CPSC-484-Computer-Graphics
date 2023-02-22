#ifndef __PLANE__
#define __PLANE__

#include "GeometricObjects/GeometricObject.h"

//=====================================
// Plane
//=====================================
//
class Plane: public GeometricObject {
public:
    Plane();
    Plane(const Point3D& point, const Normal& normal);

    Plane(const Plane& plane);

    Plane& operator= (const Plane& rhs);
    virtual ~Plane();

    virtual Plane* clone() const;


    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
    virtual bool shadow_hit(const Ray& ray, double& tmin) const;


private:
    Point3D  a;   				// point through which plane passes
    Normal 	 n;					// normal to the plane

    static constexpr double kEpsilon = 0.001;   // for shadows and secondary rays
};


#endif
