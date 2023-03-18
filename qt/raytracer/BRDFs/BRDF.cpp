// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Utilities/Constants.h"
#include "BRDFs/BRDF.h"

// ---------------------------------------------------------- default constructor
BRDF::BRDF( void ) : sampler_ptr( NULL ) {}

BRDF::BRDF( const BRDF &other ) : BRDF() { copy( other ); }

BRDF &BRDF::operator=( const BRDF &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void BRDF::copy( const BRDF &other ) {
  Sampler *psamp = other.sampler_ptr;
  sampler_ptr    = psamp ? psamp->clone() : NULL;
}

BRDF::~BRDF( void ) {
  if ( sampler_ptr ) { delete sampler_ptr; }
}

void BRDF::set_sampler( Sampler *sPtr ) {
  sampler_ptr = sPtr;
  sampler_ptr->map_samples_to_hemisphere( 1 );    // for perfect diffuse
}

RGBColor BRDF::f( const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi ) const {
  ShadeRec unused_sr = sr;    // eliminate unused warning
  Vector3D unused_wo = wo;    // eliminate unused warning
  Vector3D unused_wi = wi;    // eliminate unused warning
  return ( black );
}

// ------------------------------------------------------------------------ sample_f
RGBColor BRDF::sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wi ) const {
  ShadeRec unused_sr = sr;    // eliminate unused warning
  Vector3D unused_wo = wo;    // eliminate unused warning
  Vector3D unused_wi = wi;    // eliminate unused warning
  return ( black );
}

// ------------------------------------------------------------------------ sample_f
RGBColor BRDF::sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wi, float &pdf ) const {
  ShadeRec unused_sr  = sr;     // eliminate unused warning
  Vector3D wo_unused  = wo;     // eliminate unused warning
  Vector3D unused_wi  = wi;     // eliminate unused warning
  float    unused_pdf = pdf;    // eliminate unused warning
  unused_pdf++;
  return ( black );
}

// ------------------------------------------------------------------------ rho
RGBColor BRDF::rho( const ShadeRec &sr, const Vector3D &wo ) const {
  ShadeRec unused_sr = sr;    // eliminate unused warning
  Vector3D unused_wo = wo;    // eliminate unused warning
  return ( black );
}
