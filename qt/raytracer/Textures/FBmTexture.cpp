//#include "FBmTexture.h"

//#include "Utilities/Maths.h"
//#include "Noises/CubicNoise.h"

//FBmTexture::FBmTexture()
//: Texture(),
//  noise_ptr(NULL),
//  color(white),
//  min_value(0.0),
//  max_value(1.0) { }

//FBmTexture::FBmTexture(LatticeNoise* noise, const RGBColor& c, const float min, const float max)
//: Texture(),
//  noise_ptr(noise),
//  color(c),
//  min_value(min),
//  max_value(max) { }

//FBmTexture::FBmTexture(const FBmTexture& fbm)
//: Texture(fbm),
//  color(fbm.color),
//  min_value(fbm.min_value),
//  max_value(fbm.max_value) {

//    if (noise_ptr) { delete noise_ptr;  noise_ptr = NULL; }
//  if (fbm.noise_ptr) {set_noise_ptr(fbm.noise_ptr->clone());
//  } else {
//    set_noise_ptr(NULL);
//  }
//}

//FBmTexture& FBmTexture::operator=(const FBmTexture& rhs) {
//  if (this == &rhs) { return *this; }

//  Texture::operator=(rhs);

//  if (noise_ptr) { delete noise_ptr;  set_noise_ptr(NULL); }

//  if (rhs.noise_ptr) { set_noise_ptr(rhs.noise_ptr->clone()); }

//  color = rhs.color;
//  min_value = rhs.min_value;
//  max_value = rhs.max_value;

//  return *this;
//}

//FBmTexture* FBmTexture::clone(void) const { return new FBmTexture(*this); }

//void FBmTexture::set_noise(LatticeNoise* _noise_ptr) { set_noise_ptr(_noise_ptr); }

//void FBmTexture::set_num_octaves(const int _num_octaves) { noise_ptr->set_num_octaves(_num_octaves); }

//void FBmTexture::set_lacunarity(const float _lacunarity) { noise_ptr->set_lacunarity(_lacunarity); }

//void FBmTexture::set_gain(const float _gain) { noise_ptr->set_gain(_gain); }

//void FBmTexture::set_color(const RGBColor& c) { color = c; }

//void FBmTexture::set_color(const float r,  const float g, const float b) {
//  color.r = r;   color.b = b;   color.g = g;
//}

//void FBmTexture::set_color(const float c) { color.r = color.b = color.g = c; }

//void FBmTexture::set_min_value(const float m) { min_value = m; }

//void FBmTexture::set_max_value(const float m) { max_value = m; }

//RGBColor FBmTexture::get_color(const ShadeRec& sr) const {
//    float value = noise_ptr->value_fbm(sr.local_hit_point);
//    value = min_value + (max_value - min_value) * value;

//    return (value * color);
//}
