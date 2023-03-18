#include "Ambient.h"

// ---------------------------------------------------------------------- default constructor

Ambient::Ambient() : Light(), ls( 1.0 ), color( 1.0 ) { set_shadows( cast_shadows() ); }
// ---------------------------------------------------------------------- copy constructor

Ambient::Ambient( const Ambient &other ) : Ambient() { copy( other ); }

// ---------------------------------------------------------------------- clone
Ambient &Ambient::operator=( const Ambient &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void Ambient::copy( const Ambient &other ) {
  Ambient::operator=( other );

  ls    = other.ls;
  color = other.color;
  set_shadows( cast_shadows() );
}

// ---------------------------------------------------------------------- destructor
Ambient::~Ambient() {}

Ambient *Ambient::clone() const { return ( new Ambient( *this ) ); }

void Ambient::scale_radiance( const float b ) { ls = b; }

void Ambient::set_color( const float c ) { color.r = color.g = color.b = c; }

void Ambient::set_color( const RGBColor &c ) { color = c; }

void Ambient::set_color( const float r, const float g, const float b ) {
  color.r = r;
  color.g = g;
  color.b = b;
}
// ---------------------------------------------------------------------- get_direction

Vector3D Ambient::get_direction( ShadeRec & ) { return ( Vector3D( 0.0 ) ); }
// ---------------------------------------------------------------------- L

RGBColor Ambient::L( ShadeRec & ) { return ( ls * color ); }
