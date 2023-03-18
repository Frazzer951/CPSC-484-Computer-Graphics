#ifndef __WRAPPED_TWO_COLORS__
#define __WRAPPED_TWO_COLORS__

#include "FBmTexture.h"
#include "Noises/LatticeNoise.h"
#include "Utilities/RGBColor.h"

class WrappedTwoColors : public FBmTexture {
public:
  WrappedTwoColors( void );
  WrappedTwoColors( LatticeNoise *noise, const RGBColor &c = RGBColor( 1.0 ), const float min = 0.0, const float max = 1.0 );
  WrappedTwoColors( const WrappedTwoColors &fbm );
  WrappedTwoColors         &operator=( const WrappedTwoColors &rhs );
  virtual WrappedTwoColors *clone( void ) const;
  virtual ~WrappedTwoColors( void );

  virtual RGBColor get_color( const ShadeRec &sr ) const;

private:
};

#endif
