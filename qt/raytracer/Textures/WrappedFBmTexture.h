#ifndef __WRAPPED_FMB_TEXTURE__
#define __WRAPPED_FMB_TEXTURE__

#include "Noises/LatticeNoise.h"
#include "Utilities/RGBColor.h"
#include "FBmTexture.h"

class WrappedFBmTexture : public FBmTexture {
public:
  WrappedFBmTexture( void );
  WrappedFBmTexture( LatticeNoise *noise, const RGBColor &c = RGBColor( 1.0 ), const float min = 0.0, const float max = 1.0 );
  WrappedFBmTexture( const WrappedFBmTexture &fbm );
  WrappedFBmTexture         &operator=( const WrappedFBmTexture &rhs );
  virtual WrappedFBmTexture *clone( void ) const;
  virtual ~WrappedFBmTexture( void );

  virtual RGBColor get_color( const ShadeRec &sr ) const;

private:
};

#endif
