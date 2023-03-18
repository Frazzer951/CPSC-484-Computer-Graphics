#include "Material.h"

Material::Material() {}

Material::Material( const Material & /* other */ ) : Material() {}

Material &Material::operator=( const Material &other ) {
  if ( this == &other ) { return *this; }
  return *this;
}

Material::~Material() {}

RGBColor Material::shade( ShadeRec & ) { return black; }

RGBColor Material::area_light_shade( ShadeRec & /* sr */ ) { return black; }

RGBColor Material::path_shade( ShadeRec & ) { return black; }

RGBColor Material::get_Le( ShadeRec & /* sr */ ) const { return white; }
