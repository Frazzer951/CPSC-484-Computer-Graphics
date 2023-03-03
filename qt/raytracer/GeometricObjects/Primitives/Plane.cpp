#include "Plane.h"


Plane::Plane()
    : 	GeometricObject(),
        a(0.0),
        n(0, 1, 0)
{}

Plane::Plane(const Point3D& point, const Normal& normal)
    :	GeometricObject(),
        a(point),
        n(normal) { n.normalize(); }

Plane::Plane(const Plane& plane) :	GeometricObject(plane), a(plane.a), n(plane.n) { }

Plane& Plane::operator= (const Plane& rhs) {
    if (this == &rhs)
        return (*this);

    GeometricObject::operator= (rhs);
    a = rhs.a;
    n = rhs.n;
    return (*this);
}

Plane::~Plane() { }

Plane* Plane::clone() const { 	return (new Plane(*this)); }

bool
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    float t = (a - ray.o).dot(n) / (ray.d.dot(n));

    if (t > kEpsilon) {
        tmin = t;
        sr.normal = n;
        sr.local_hit_point = ray.o + t * ray.d;
        return (true);
    }
    return(false);
}

bool Plane::shadow_hit(const Ray& ray, double& tmin) const {
    if (!shadows) { return false; }

    // TODO: implement shadow_hit testing
    return false;
}





