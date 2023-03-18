#ifndef __FBM_TEXTURE__
#define __FBM_TEXTURE__

#include "Texture.h"
#include "Noises/LatticeNoise.h"
#include "Utilities/RGBColor.h"

class FBmTexture : public Texture {
public:
  FBmTexture( void );
  FBmTexture( LatticeNoise *noise, const RGBColor &c = RGBColor( 1.0 ), const float min = 0.0, const float max = 1.0 );
  FBmTexture( const FBmTexture &fbm );
  FBmTexture         &operator=( const FBmTexture &rhs );
  virtual FBmTexture *clone( void ) const;
  virtual ~FBmTexture( void );

  void set_noise( LatticeNoise *_noise_ptr );
  void set_num_octaves( const int _num_octaves );
  void set_lacunarity( const float _lacunarity );
  void set_gain( const float _gain );
  void set_color( const RGBColor &c );
  void set_color( const float r, const float g, const float b );
  void set_color( const float c );
  void set_min_value( const float m );
  void set_max_value( const float m );

  virtual RGBColor get_color( const ShadeRec &sr ) const;

  void set_noise_ptr( LatticeNoise *ptr );

protected:
  LatticeNoise *noise_ptr;
  //    std::shared_ptr<LatticeNoise> noise_ptr;
  RGBColor      color;
  float         min_value;    // scaling factor
  float         max_value;    // scaling factor
};

inline void set_noise_ptr( LatticeNoise *ptr );

#endif
