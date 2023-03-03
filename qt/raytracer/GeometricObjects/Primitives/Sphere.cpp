#include "Sphere.h"
#include "Utilities/Maths.h"

//// ---------------------------------------------------------------- default constructor



Sphere::Sphere() : Sphere(0.0, 1.0) { }

Sphere::Sphere(Point3D pt, double r) : GeometricObject(), center(pt), radius(r) { }

Sphere::Sphere(const Sphere& s)
: GeometricObject(s), center(s.center), radius(s.radius) { }

Sphere& Sphere::operator=(const Sphere& s) {
    if (this == &s) { return (*this); }
    GeometricObject::operator= (s);
    center 	= s.center;
    radius	= s.radius;
    return (*this);
}

Sphere::~Sphere() { }

Sphere* Sphere::clone() const { return (new Sphere(*this)); }

void Sphere::set_center(const Point3D& c) { center = c; };

void Sphere::set_center(const double x, const double y, const double z) {
    center.x = x;  center.y = y;  center.z = z;
}

void Sphere::set_radius(const double r) { radius = r; }

//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double 		t;
    Vector3D	temp 	= ray.o - center;
//    double 		a 		= ray.d * ray.d;
//    double 		b 		= 2.0 * temp * ray.d;
//    double 		c 		= temp * temp - radius * radius;
//    double 		disc	= b * b - 4.0 * a * c;

    double      a       = ray.d.dot(ray.d);
    double      b       = 2.0 * temp.dot(ray.d);
    double      c       = temp.dot(temp) - radius * radius;
    double      disc    = b * b - 4.0 * a * c;

    if (disc < 0.0)
        return(false);
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root
	
        if (t > kEpsilon) {
            tmin = t;
            sr.normal 	 = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }
	
        t = (-b + e) / denom;    // larger root
	
        if (t > kEpsilon) {
            tmin = t;
            sr.normal   = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }
    }
	
    return (false);
}

bool Sphere::shadow_hit(const Ray&, double&) const {
    if (!shadows) { return false; }

    // TODO: implement shadow_hit testing
    return false;
}
// ---------------------------------------------------------------- sample







