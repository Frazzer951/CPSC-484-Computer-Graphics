// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "BTDF.h"

// ------------------------------------------------------------------------ default constructor
BTDF::BTDF( void ) : sampler_ptr( NULL ) {}

// ------------------------------------------------------------------------ copy constructor
BTDF::BTDF( const BTDF &other ) : BTDF() { copy( other ); }

BTDF &BTDF::operator=( const BTDF &rhs ) {
  if ( this == &rhs ) { return ( *this ); }
  return ( *this );
}

void BTDF::copy( const BTDF &other ) {
  Sampler *psamp = other.sampler_ptr;
  sampler_ptr    = psamp ? psamp->clone() : NULL;
}

// ------------------------------------------------------------------------ destructor
BTDF::~BTDF( void ) {
  if ( sampler_ptr ) { delete sampler_ptr; }
}

// ------------------------------------------------------------------------ assignment operator
// ------------------------------------------------------------------------ f
RGBColor BTDF::f( const ShadeRec &, const Vector3D &, const Vector3D & ) const { return ( black ); }
// ------------------------------------------------------------------------ sample_f
RGBColor BTDF::sample_f( const ShadeRec &, const Vector3D &, Vector3D & ) const { return ( black ); }
// ------------------------------------------------------------------------ rho
RGBColor BTDF::rho( const ShadeRec &, const Vector3D & ) const { return ( black ); }
// ------------------------------------------------------------------------ rho
