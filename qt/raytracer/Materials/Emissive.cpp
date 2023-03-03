//#include "Emissive.h"
//#include "Utilities/RGBColor.h"

//RGBColor black(0, 0, 0);
//RGBColor white(255, 255, 255);

//Emissive::Emissive(void)
//: ls(1), ce(white) { }

//Emissive*
//Emissive::clone(void) const {
//    return (new Emissive(*this));
//}

//Emissive::Emissive(const Emissive& o) { copy(o); }
//Emissive& Emissive::operator=(const Emissive& o) {
//  if (this != &o) { copy(o); }
//  return *this;
//}

//Emissive::~Emissive() { }

//void Emissive::scale_radiance(const float _ls) { ls = _ls; }

//void Emissive::set_ce(const float r, const float g, const float b) {
//  ce = RGBColor(r, g, b);
//}

//RGBColor Emissive::get_Le(ShadeRec& ) const { return black; }

//RGBColor Emissive::shade(ShadeRec& ) { return black; }

//RGBColor Emissive::area_light_shade(ShadeRec& sr) {
//  if (-sr.normal.dot(sr.ray.d) > 0.0) { return ls * ce;
//  } else {
//    return black;
//  }
//}

//void Emissive::copy(const Emissive& o) {  ls = o.ls; ce = o.ce; }
