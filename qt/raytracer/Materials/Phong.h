#ifndef __PHONG_H__
#define __PHONG_H__

#include "BRDFs/Lambertian.h"
#include "BRDFs/GlossySpecular.h"

#include "World/World.h"    // required for the shade function in all derived classes
#include "Utilities/RGBColor.h"
#include "Utilities/ShadeRec.h"
#include "Materials/Material.h"

class Phong : public Material {
public:
  Phong( void );
  Phong( const Phong &o );
  Phong &operator=( const Phong &o );

  ~Phong();
  virtual Phong *clone() const;

  // contructors, etc ...
  virtual RGBColor shade( ShadeRec &sr );

  // there is no Lambertian::ka data member because ambient reflection
  // is diffuse reflection
  void set_ka( const float ka );

  // this also sets Lambertian::kd, but for a different Lambertian object
  void set_kd( const float kd );

  void set_cd( const RGBColor c );
  void set_cd( const float r, const float g, const float b );
  void set_cd( const float c );

  void set_ks( const float ks );
  void set_exp( const float exp );

  void set_cs( const RGBColor &c );
  void set_cs( const float r, const float g, const float b );
  void set_cs( const float c );

private:
  void copy( const Phong &other );

protected:
  Lambertian     *ambient_brdf;
  Lambertian     *diffuse_brdf;
  GlossySpecular *specular_brdf;
};

#endif    // __PHONG_H__
