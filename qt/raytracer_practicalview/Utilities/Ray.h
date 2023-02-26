#ifndef __RAY__
#define __RAY__

#include "Point3D.h"
#include "Vector3D.h"


//=====================================
// Ray
//=====================================
//
typedef struct Ray Ray;


struct Ray {
    Ray() : o(0.0), d(0.0, 0.0, 1.0) { }
    Ray(const Point3D& origin, const Vector3D& dir) : o(origin), d(dir) { }

    Ray(const Ray& ray) : o(ray.o), d(ray.d) { }
    Ray& operator= (const Ray& ray) {
        if (this != &ray) { o = ray.o;  d = ray.d; }  return *this;
    }
    ~Ray() { }


    Point3D	  o;   // origin
    Vector3D  d;   // direction
};

#endif
