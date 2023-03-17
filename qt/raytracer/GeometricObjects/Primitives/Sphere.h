#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObjects/GeometricObject.h"

//=====================================
// Sphere
//=====================================
//
class Sphere : public GeometricObject {
public:
  Sphere();
  Sphere( Point3D pt, double r );

  Sphere( const Sphere &s );
  Sphere &operator=( const Sphere &s );
  virtual ~Sphere();

  virtual Sphere *clone() const;

  void set_center( const Point3D &c );
  void set_center( const double x, const double y, const double z );
  void set_radius( const double r );

  virtual bool hit( const Ray &ray, double &t, ShadeRec &s ) const;
  virtual bool shadow_hit( const Ray &ray, double &tmin ) const;

private:
  Point3D                 center;
  double                  radius;
  static constexpr double kEpsilon = 0.001;    // for shadows and secondary rays
};

#endif
