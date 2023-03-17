#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Lights/Light.h"
#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"

#include "World/World.h"    // you will need this later on for shadows
#include "Utilities/ShadeRec.h"

//=====================================
// Directional
//=====================================
//
class Directional : public Light {
public:
  Directional();

  Directional( const Directional &dl );
  Directional &operator=( const Directional &rhs );

  virtual ~Directional();
  virtual Light *clone() const;

  void scale_radiance( const float b );

  void set_color( const float c );
  void set_color( const RGBColor &c );
  void set_color( const float r, const float g, const float b );

  void             set_direction( Vector3D d );
  void             set_direction( float dx, float dy, float dz );
  virtual Vector3D get_direction( ShadeRec &sr );

  virtual RGBColor L( ShadeRec &sr );

private:
  float    ls;
  RGBColor color;
  Vector3D dir;    // direction the light comes from
};

#endif
