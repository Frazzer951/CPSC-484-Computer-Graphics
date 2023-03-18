//#include "WrappedTwoColors.h"
//#include "Utilities/Constants.h"

//WrappedTwoColors::WrappedTwoColors()
//: FBmTexture(NULL, white, 0.0, 1.0) { }

//WrappedTwoColors::WrappedTwoColors(LatticeNoise* noise, const RGBColor& c, const float min, const float max)
//: FBmTexture(noise, c, min, max) { }

//WrappedTwoColors::WrappedTwoColors(const WrappedTwoColors& fbm)
//: FBmTexture(fbm.noise_ptr, fbm.color, fbm.min_value, fbm.max_value) {
//  if (fbm.noise_ptr) { fbm.noise_ptr.reset(fbm.noise_ptr->clone());
//  else {
//    noise_ptr.reset(NULL);
//  }
//}

//WrappedTwoColors& WrappedTwoColors::operator=(const WrappedTwoColors& rhs) {
//  if (this == &rhs) { return *this; }

//  Texture::operator=(rhs);

//  if (noise_ptr) { noise_ptr.reset(NULL); }

//  if (rhs.noise_ptr) { noise_ptr.reset(rhs.noise_ptr->clone()); }

//  color = rhs.color;
//  min_value = rhs.min_value;
//  max_value = rhs.max_value;

//  return *this;
//}

//WrappedTwoColors::~WrappedTwoColors(void) { }

//WrappedTwoColors* WrappedTwoColors::clone(void) const {
//    return new WrappedTwoColors(*this);
//}

//RGBColor WrappedTwoColors::get_color(const ShadeRec& sr) const {
//    float noise = expansion_number * noise_ptr->value_fBm(sr.local_hit_point);
//    float value = noise - floor(noise);

//    if (noise < 1.0)
//        return (value * color1);
//    else
//        return (value * color2);
//}
