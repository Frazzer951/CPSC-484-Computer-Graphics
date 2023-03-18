// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Lambertian.h"
#include "Utilities/Constants.h"

// ---------------------------------------------------------------------- default constructor
Lambertian::Lambertian( void ) : BRDF(), kd( 0.0 ), cd( 0.0 ) {}

// ---------------------------------------------------------------------- copy constructor
Lambertian::Lambertian( const Lambertian &other ) : Lambertian() { copy( other ); }

// ---------------------------------------------------------------------- assignment operator
Lambertian &Lambertian::operator=( const Lambertian &other ) {
  if ( this == &other ) { copy( other ); }
  return ( *this );
}

void Lambertian::copy( const Lambertian &other ) {
  BRDF::operator=( other );

  kd = other.kd;
  cd = other.cd;
}

// ---------------------------------------------------------------------- destructor
Lambertian::~Lambertian( void ) {}
// ---------------------------------------------------------------------- clone

Lambertian *Lambertian::clone( void ) const { return ( new Lambertian( *this ) ); }

// ---------------------------------------------------------------------- f
// there is no sampling here

RGBColor Lambertian::f( const ShadeRec &, const Vector3D &, const Vector3D & ) const { return ( kd * cd * invPI ); }
// ---------------------------------------------------------------------- sample_f
// this generates a direction by sampling the hemisphere with a cosine distribution
// this is called in path_shade for any material with a diffuse shading component
// the samples have to be stored with a cosine distribution

RGBColor Lambertian::sample_f( const ShadeRec &sr, const Vector3D &, Vector3D &wi, float &pdf ) const {
  Vector3D w = sr.normal;
  Vector3D v = Vector3D( 0.0034, 1, 0.0071 ).cross( w );
  v.normalize();
  Vector3D u = v.cross( w );

  Point3D sp = sampler_ptr->sample_hemisphere();
  wi         = sp.x * u + sp.y * v + sp.z * w;
  wi.normalize();

  pdf = sr.normal.dot( wi ) * invPI;
  return ( kd * cd * invPI );
}
// ---------------------------------------------------------------------- rho
RGBColor Lambertian::rho( const ShadeRec &, const Vector3D & ) const { return ( kd * cd ); }
