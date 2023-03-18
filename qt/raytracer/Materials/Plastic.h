#ifndef PLASTIC_H
#define PLASTIC_H

#include "Material.h"
#include "BRDFs/Lambertian.h"
#include "BRDFs/GlossySpecular.h"
#include "BRDFs/BRDF.h"

class Plastic : public Material {
public:
  Plastic( void );
  Plastic( const Plastic &p );
  virtual Plastic *clone( void ) const;
  Plastic         &operator=( const Plastic &rhs );
  virtual ~Plastic( void );

  virtual RGBColor shade( ShadeRec &sr );

private:
  void copy( const Plastic &other );

protected:
  Lambertian     *ambient_brdf;
  Lambertian     *diffuse_brdf;
  GlossySpecular *specular_brdf;
};

#endif    // PLASTIC_H
