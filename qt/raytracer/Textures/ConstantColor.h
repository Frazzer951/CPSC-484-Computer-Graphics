#ifndef __CONSTANTCOLOR__
#define __CONSTANTCOLOR__

#include "Texture.h"

class ConstantColor : public Texture {
public:
  ConstantColor( void );
  ConstantColor( const RGBColor &color );
  ConstantColor( const ConstantColor &cc );
  ConstantColor &operator=( const ConstantColor &cc );
  ~ConstantColor();
  virtual ConstantColor *clone() const;

  void set_color( const RGBColor &c );

  virtual RGBColor get_color( const ShadeRec &sr ) const;

private:
  void copy( const ConstantColor &other );

  RGBColor color;    // the color
};

#endif
