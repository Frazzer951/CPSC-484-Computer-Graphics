#include "PlaneChecker.h"

PlaneChecker::PlaneChecker( void ) :
    Texture(), size( 1.0 ), outline_width( 1.0 ),

    color1( 1.0 ), color2( 0.0 ), outline_color( 0.0 ) {}

PlaneChecker::PlaneChecker( const PlaneChecker &other ) : PlaneChecker() { copy( other ); }

PlaneChecker &PlaneChecker::operator=( const PlaneChecker &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void PlaneChecker::copy( const PlaneChecker &other ) {
  Texture::operator=( other );

  size          = other.size;
  color1        = other.color1;
  color2        = other.color2;
  outline_width = other.outline_width;
  outline_color = other.outline_color;
}

PlaneChecker::~PlaneChecker() {}

PlaneChecker *PlaneChecker::clone() const { return new PlaneChecker(); }
void          PlaneChecker::set_size( const float s ) { size = s; }

void PlaneChecker::set_outline_width( const float s ) { outline_width = s; }

void PlaneChecker::set_color1( const RGBColor &c ) { color1 = c; }

void PlaneChecker::set_color1( const float c ) {
  color1.r = c;
  color1.g = c;
  color1.b = c;
}

void PlaneChecker::set_color1( const float r, const float g, const float b ) {
  color1.r = r;
  color1.g = g;
  color1.b = b;
}

void PlaneChecker::set_color2( const RGBColor &c ) { color2 = c; }

void PlaneChecker::set_color2( const float c ) { color2.r = color2.g = color2.b = c; }

void PlaneChecker::set_color2( const float r, const float g, const float b ) {
  color2.r = r;
  color2.g = g;
  color2.b = b;
}

void PlaneChecker::set_outline_color( const RGBColor &c ) { outline_color = c; }

void PlaneChecker::set_outline_color( const float c ) { outline_color.r = outline_color.g = outline_color.b = c; }

void PlaneChecker::set_outline_color( const float r, const float g, const float b ) {
  outline_color.r = r;
  outline_color.g = g;
  outline_color.b = b;
}

RGBColor PlaneChecker::get_color( const ShadeRec &sr ) const {
  float x = sr.local_hit_point.x;
  float z = sr.local_hit_point.z;

  int ix = floor( x / size );
  int iz = floor( z / size );

  float fx    = x / size - ix;
  float fz    = z / size - iz;
  float width = 0.5 * outline_width / size;

  bool in_outline = ( fx < width || fx > 1.0 - width ) || ( fz < width || fz > 1.0 - width );

  if ( ( ix + iz ) % 2 == 0 ) {
    if ( !in_outline ) { return ( color1 ); }
  } else {
    if ( !in_outline ) { return ( color2 ); }
  }

  return ( outline_color );
}
