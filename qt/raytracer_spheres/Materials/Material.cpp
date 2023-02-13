#include "Material.h"


Material::Material() { }

Material::Material(const Material&) { }  // does nothing

Material& Material::operator=(const Material& rhs) { if (this == &rhs) { return *this; }  return *this; }   // does nothing


Material::~Material() { }

RGBColor Material::shade(ShadeRec&) { return black; }



