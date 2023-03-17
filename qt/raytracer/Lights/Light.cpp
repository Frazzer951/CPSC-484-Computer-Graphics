#include "Light.h"
#include "Utilities/Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light() {}

// ---------------------------------------------------------------------- dopy constructor

Light::Light( const Light & ) {}

// ---------------------------------------------------------------------- assignment operator

Light &Light::operator=( const Light &rhs ) {
  if ( this == &rhs ) return ( *this );

  return ( *this );
}

// ---------------------------------------------------------------------- destructor

Light::~Light() {}

// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor Light::L( ShadeRec & ) { return ( black ); }
