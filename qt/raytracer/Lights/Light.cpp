#include "Light.h"
#include "Utilities/Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light() : shadows( true ) {}

Light::Light( const Light &pl ) : Light() { copy( pl ); }

Light &Light::operator=( const Light &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Light::copy( const Light &other ) { set_shadows( other.cast_shadows() ); }

// ---------------------------------------------------------------------- destructor

Light::~Light() {}

// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor Light::L( ShadeRec & ) { return ( black ); }

float Light::G( const ShadeRec & ) const { return 1.0; }

float Light::pdf( const ShadeRec & ) const { return 1.0; }

void Light::set_shadows( bool shadows_on ) { shadows = shadows_on; }

bool Light::cast_shadows() const { return shadows; }

bool Light::in_shadow( const Ray & /*ray*/, const ShadeRec & /*sr*/ ) const { return false; }
