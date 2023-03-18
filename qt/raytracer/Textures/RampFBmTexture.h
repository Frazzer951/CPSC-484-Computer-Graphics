#ifndef __RAMP_FBM_TEXTURE__
#define __RAMP_FBM_TEXTURE__

#include "Noises/LatticeNoise.h"
#include "Utilities/RGBColor.h"
#include "Utilities/ShadeRec.h"

class RampFBmTexture : public FBmTexture {
public:
  // constructors, etc.
  virtual RGBColor get_color( const ShadeRec &sr ) const;

  //   void set_noise(LatticeNoise* _noise_ptr);     // all inherited
  //   void set_num_octaves(const int _num_octaves);
  //   void set_lacunarity(const float _lacunarity);
  //   void set_gain(const float _gain);
  //   void set_color(const RGBColor& c);
  //   void set_color(const float r,  const float g, const float b);
  //   void set_color(const float c);
  //   void set_min_value(const float m);
  //   void set_max_value(const float m);

private:
  // LatticeNoise* noise_ptr;          // all inherited
  // RGBColor color;
  // float min_value, max_value;       // scaling factors
};

#endif
