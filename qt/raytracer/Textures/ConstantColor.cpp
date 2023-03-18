#include "ConstantColor.h"
#include "Utilities/Constants.h"

ConstantColor::ConstantColor() : Texture(), color( white ) {}

ConstantColor::ConstantColor( const ConstantColor &other ) : ConstantColor() { copy( other ); }

ConstantColor &ConstantColor::operator=( const ConstantColor &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void ConstantColor::copy( const ConstantColor &other ) {
  Texture::operator=( other );
  color = other.color;
}

ConstantColor::~ConstantColor( void ) {}

ConstantColor *ConstantColor::clone( void ) const { return new ConstantColor( *this ); }

RGBColor ConstantColor::get_color( const ShadeRec & /*sr*/ ) const { return color; }
