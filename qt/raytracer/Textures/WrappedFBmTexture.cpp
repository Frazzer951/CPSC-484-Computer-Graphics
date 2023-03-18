//#include "WrappedFBmTexture.h"
//#include "Utilities/Constants.h"

//WrappedFBmTexture::WrappedFBmTexture()
//: FBmTexture(NULL, white, 0.0, 1.0) { }

//WrappedFBmTexture::WrappedFBmTexture(LatticeNoise* noise, const RGBColor& c, const float min, const float max)
//: FBmTexture(noise, c, min, max) { }

//WrappedFBmTexture::WrappedFBmTexture(const WrappedFBmTexture& fbm)
//: FBmTexture(fbm, fbm.color, fbm.min_value, fbm.max_value) {
//  if (fbm.noise_ptr) { fbm.noise_ptr.reset(fbm.noise_ptr->clone());
//  } else {
//    noise_ptr.reset(NULL);
//  }
//}

//WrappedFBmTexture& WrappedFBmTexture::operator=(const WrappedFBmTexture& rhs) {
//  if (this == &rhs) { return *this; }

//  Texture::operator=(rhs);

//  if (noise_ptr) { noise_ptr->reset(NULL); }

//  if (rhs.noise_ptr) { noise_ptr.reset(rhs.noise_ptr->clone()); }

//  color = rhs.color;
//  min_value = rhs.min_value;
//  max_value = rhs.max_value;

//  return *this;
//}

//WrappedFBmTexture::~WrappedFBmTexture(void) { }

//WrappedFBmTexture* WrappedFBmTexture::clone(void) const {
//    return new WrappedFBmTexture(*this);
//}

//RGBColor WrappedFBmTexture::get_color(const ShadeRec& sr) const {
//    float noise = expansion_number * noise_ptr->value_fBm(sr.local_hit_point);
//    float value = noise - floor(noise);

//    return (value * color);
//}
