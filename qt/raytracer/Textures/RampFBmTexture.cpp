//#include "RampFBmTexture.h"

//RampFBmTexture::RampFBmTexture()
//: FBmTexture(NULL, white, 0.0, 1.0) { }

//RampFBmTexture::RampFBmTexture(LatticeNoise* noise, const RGBColor& c, const float min, const float max)
//: FBmTexture(noise, color, min, max) { }

//RampFBmTexture::RampFBmTexture(const RampFBmTexture& fbm):
//  FBmTexture(NULL, fbm.color, fbm.min, fbm.max) { }

//  if (fbm.noise_ptr) { noise_ptr->reset(fbm.noise_ptr->clone());
//  else {
//    noise_ptr->reset(NULL);
//  }
//}

//RampFBmTexture& RampFBmTexture::operator=(const RampFBmTexture& rhs) {
//  if (this == &rhs) { return *this; }

//  Texture::operator=(rhs);

//  if (noise_ptr) { noise_ptr->reset(NULL); }

//  if (rhs.noise_ptr) { noise_ptr ->reset(rhs.noise_ptr->clone()); }

//  color = rhs.color;
//  min_value = rhs.min_value;
//  max_value = rhs.max_value;

//  return *this;
//}

//RampFBmTexture* RampFBmTexture::clone(void) const { return new RampFBmTexture(*this); }

//RGBColor RampRampFBmTexture::get_color(const ShadeRec& sr) const {
//    float y = sr.local_hit_point.y;
//    float u = (1.0 + sin(y)) / 2.0;
//    int row = 0;              // use top row of ramp image
//    int column = u * (ramp_ptr ->hres - 1);

//    return (ramp_ptr->get_color(row, column));
//}
