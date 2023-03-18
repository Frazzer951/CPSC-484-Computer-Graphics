// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "PerfectTransmitter.h"

// ------------------------------------------------------------------- default constructor
PerfectTransmitter::PerfectTransmitter( void ) : BTDF(), kt( 0.0 ), ior( 1.0 ) {}

// ------------------------------------------------------------------- copy constructor
PerfectTransmitter::PerfectTransmitter( const PerfectTransmitter &other ) : PerfectTransmitter() { copy( other ); }

// ------------------------------------------------------------------- assignment operator
PerfectTransmitter &PerfectTransmitter::operator=( const PerfectTransmitter &other ) {
  if ( this == &other ) { copy( other ); }
  return ( *this );
}

// ------------------------------------------------------------------- assignment operator
void PerfectTransmitter::copy( const PerfectTransmitter &other ) {
  BTDF::operator=( other );

  kt  = other.kt;
  ior = other.ior;
}

// ------------------------------------------------------------------- destructor
PerfectTransmitter::~PerfectTransmitter( void ) {}

// ------------------------------------------------------------------- clone
PerfectTransmitter *PerfectTransmitter::clone( void ) const { return ( new PerfectTransmitter( *this ) ); }

// ------------------------------------------------------------------- tir
// tests for total internal reflection
bool PerfectTransmitter::tir( const ShadeRec &sr ) const {
  Vector3D wo( -sr.ray.d );
  float    cos_thetai = sr.normal.dot( wo );
  float    eta        = ior;

  if ( cos_thetai < 0.0 ) { eta = 1.0 / eta; }

  return ( 1.0 - ( 1.0 - cos_thetai * cos_thetai ) / ( eta * eta ) < 0.0 );
}

// ------------------------------------------------------------------- f

RGBColor PerfectTransmitter::f( const ShadeRec &, const Vector3D &, const Vector3D & ) const { return ( black ); }

// ------------------------------------------------------------------- sample_f
// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

RGBColor PerfectTransmitter::sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wt ) const {
  Normal n( sr.normal );
  float  cos_thetai = n.dot( wo );
  float  eta        = ior;

  if ( cos_thetai < 0.0 ) {    // transmitted ray is outside
    cos_thetai = -cos_thetai;
    n          = -n;           // reverse direction of normal
    eta        = 1.0 / eta;    // invert ior
  }

  float temp       = 1.0 - ( 1.0 - cos_thetai * cos_thetai ) / ( eta * eta );
  float cos_theta2 = sqrt( temp );
  wt               = -wo / eta - ( cos_theta2 - cos_thetai / eta ) * n;

  return ( kt / ( eta * eta ) * white / fabs( sr.normal.dot( wt ) ) );
}

// ------------------------------------------------------------------- rho
RGBColor PerfectTransmitter::rho( const ShadeRec &, const Vector3D & ) const { return ( black ); }
