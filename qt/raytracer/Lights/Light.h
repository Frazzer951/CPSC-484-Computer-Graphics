#ifndef __LIGHT__
#define __LIGHT__

#include <memory>

#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Ray.h"

struct ShadeRec;

//=====================================
// Light
//=====================================
//
class Light {
public:
  Light();
  virtual ~Light();

  Light( const Light &ls );
  Light         &operator=( const Light &rhs );
  virtual Light *clone() const = 0;

  virtual Vector3D get_direction( ShadeRec &sr ) = 0;
  virtual RGBColor L( ShadeRec &sr );
  virtual float    G( const ShadeRec &sr ) const;
  virtual float    pdf( const ShadeRec &sr ) const;

  virtual bool in_shadow( const Ray &ray, const ShadeRec &sr ) const;

  bool cast_shadows() const;
  void set_shadows( bool shadows );

private:
  void copy( const Light &other );

  bool shadows;
};

#endif
