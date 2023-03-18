#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "Lights/Light.h"
#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"

#include "World/World.h"    // you will need this later on for shadows
#include "Utilities/ShadeRec.h"

class PointLight : public Light {
public:
  PointLight();

  PointLight( const PointLight &dl );
  PointLight &operator=( const PointLight &rhs );

  virtual ~PointLight();
  virtual PointLight *clone() const;

  void scale_radiance( const float b );

  void set_location( Vector3D d );
  void set_location( float dx, float dy, float dz );

  virtual Vector3D get_direction( ShadeRec &sr );

  virtual bool in_shadow( const Ray &ray, const ShadeRec &sr ) const;

  virtual RGBColor L( ShadeRec &sr );

private:
  void copy( const PointLight &other );

  float    ls;
  RGBColor color;
  Vector3D location;
};

#endif    // __POINT_LIGHT_H__
