// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Reflective.h"
#include "Phong.h"

// ---------------------------------------------------------------- default constructor
Reflective::Reflective( void ) : Phong(), reflective_brdf( new PerfectSpecular ) {}

// ---------------------------------------------------------------- copy constructor
Reflective::Reflective( const Reflective &other ) : Reflective() { copy( other ); }

// ---------------------------------------------------------------- assignment operator
Reflective &Reflective::operator=( const Reflective &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

// ---------------------------------------------------------------- assignment operator
void Reflective::copy( const Reflective &other ) {
  Phong::operator=( other );

  PerfectSpecular const *p = other.reflective_brdf;
  reflective_brdf          = p ? p->clone() : NULL;
}

// ---------------------------------------------------------------- clone
Reflective *Reflective::clone( void ) const { return ( new Reflective( *this ) ); }

// ---------------------------------------------------------------- destructor
Reflective::~Reflective( void ) {
  if ( reflective_brdf ) { delete reflective_brdf; }
}

// ------------------------------------------------------------------------------------ shade
RGBColor Reflective::shade( ShadeRec &sr ) {
  RGBColor L( Phong::shade( sr ) );    // Direct illumination

  Vector3D wo = -sr.ray.d;
  Vector3D wi;
  RGBColor fr = reflective_brdf->sample_f( sr, wo, wi );
  Ray      reflected_ray( sr.hit_point, wi );

  L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * ( sr.normal.dot( wi ) );

  return ( L );
}

RGBColor Reflective::area_light_shade( ShadeRec &sr ) {
  //qDebug() << "Reflective::area_light_shade";
  RGBColor L( Phong::shade( sr ) );    // Direct illumination

  Vector3D wo = -sr.ray.d;
  Vector3D wi;
  RGBColor fr = reflective_brdf->sample_f( sr, wo, wi );
  Ray      reflected_ray( sr.hit_point, wi );

  L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * ( sr.normal.dot( wi ) );

  return L;
}
