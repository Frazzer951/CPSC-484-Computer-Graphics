#ifndef __PLANECHECKER__
#define __PLANECHECKER__

#include "Texture.h"
#include "Utilities/RGBColor.h"

class PlaneChecker : public Texture {
public:
  PlaneChecker( void );
  PlaneChecker( const PlaneChecker &other );
  PlaneChecker &operator=( const PlaneChecker &other );
  virtual ~PlaneChecker( void );
  virtual PlaneChecker *clone( void ) const;

  virtual RGBColor get_color( const ShadeRec &sr ) const;

  void set_size( const float s );
  void set_outline_width( const float s );

  void set_color1( const RGBColor &c );
  void set_color1( const float r, const float g, const float b );
  void set_color1( const float c );

  void set_color2( const RGBColor &c );
  void set_color2( const float r, const float g, const float b );
  void set_color2( const float c );

  void set_outline_color( const RGBColor &c );
  void set_outline_color( const float r, const float g, const float b );
  void set_outline_color( const float c );

private:
  void copy( const PlaneChecker &other );

  float size;
  float outline_width;

  RGBColor color1;
  RGBColor color2;
  RGBColor outline_color;
};

#endif
