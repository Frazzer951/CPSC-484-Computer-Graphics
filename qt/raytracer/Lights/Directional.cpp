#include "Directional.h"

// ---------------------------------------------------------------------- default constructor

Directional::Directional() : Light(), ls( 1.0 ), color( 1.0 ), dir( 0, 1, 0 ) { set_shadows( true ); }

Directional::Directional( const Directional &pl ) : Directional() { copy( pl ); }

Directional &Directional::operator=( const Directional &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Directional::copy( const Directional &other ) {
  Light::operator=( other );

  ls    = other.ls;
  color = other.color;
  dir   = other.dir;
  set_shadows( other.cast_shadows() );
}

Directional *Directional::clone() const { return ( new Directional( *this ) ); }

// ---------------------------------------------------------------------- destructor
Directional::~Directional() {}

void Directional::scale_radiance( const float b ) { ls = b; }

void Directional::set_color( const float c ) { color.r = color.g = color.b = c; }

void Directional::set_color( const RGBColor &c ) { color = c; }

void Directional::set_color( const float r, const float g, const float b ) {
  color.r = r;
  color.g = g;
  color.b = b;
}

void Directional::set_direction( Vector3D d ) {
  dir = d;
  dir.normalize();
}

void Directional::set_direction( float dx, float dy, float dz ) {
  dir.x = dx;
  dir.y = dy;
  dir.z = dz;
  dir.normalize();
}

bool Directional::in_shadow( const Ray &ray, const ShadeRec &sr ) const {
  double t;
  int    num_objects = sr.w.objects.size();

  for ( int j = 0; j < num_objects; j++ ) {
    if ( sr.w.objects[j]->shadow_hit( ray, t ) ) return true;
  }
  return false;
}

// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined

Vector3D Directional::get_direction( ShadeRec & ) { return ( dir ); }

// ------------------------------------------------------------------------------  L

RGBColor Directional::L( ShadeRec & ) { return ( ls * color ); }
