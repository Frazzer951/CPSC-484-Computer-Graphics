#include "Transparent.h"

#include <cmath>

// ---------------------------------------------------------------- default constructor
Transparent::Transparent( void ) : Phong(), reflective_brdf( new PerfectSpecular ), specular_btdf( new PerfectTransmitter ) {}

// ---------------------------------------------------------------- copy constructor
Transparent::Transparent( const Transparent &other ) : Transparent() { copy( other ); }

// ---------------------------------------------------------------- assignment operator
Transparent &Transparent::operator=( const Transparent &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Transparent::copy( const Transparent &other ) {
  Phong::operator=( other );

  PerfectSpecular    *prefl = other.reflective_brdf;
  PerfectTransmitter *pspec = other.specular_btdf;

  reflective_brdf = prefl ? prefl->clone() : NULL;
  specular_btdf   = pspec ? pspec->clone() : NULL;
}

// ---------------------------------------------------------------- destructor
Transparent::~Transparent( void ) {
  if ( reflective_brdf ) { delete reflective_brdf; }
  if ( specular_btdf ) { delete specular_btdf; }
}

// ---------------------------------------------------------------- clone
Transparent *Transparent::clone( void ) const { return new Transparent( *this ); }

RGBColor Transparent::shade( ShadeRec &sr ) {
  RGBColor L( Phong::shade( sr ) );

  Vector3D wo = -sr.ray.d;
  Vector3D wi;
  RGBColor fr = reflective_brdf->sample_f( sr, wo, wi );    // computes wi
  Ray      reflected_ray( sr.hit_point, wi );

  if ( specular_btdf->tir( sr ) ) {
    //     if (specular_btdf) {
    L += sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 );
  } else {    // kr = 1.0
    Vector3D wt;
    RGBColor ft = specular_btdf->sample_f( sr, wo, wt );    // computes wt
    Ray      transmuted_ray( sr.hit_point, wt );

    L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * std::fabs( sr.normal.dot( wi ) );
    L += ft * sr.w.tracer_ptr->trace_ray( transmuted_ray, sr.depth + 1 ) * std::fabs( sr.normal.dot( wt ) );
  }
  return L;
}

RGBColor Transparent::area_light_shade( ShadeRec &sr ) {
  RGBColor L( Phong::shade( sr ) );

  Vector3D wo = -sr.ray.d;
  Vector3D wi;
  RGBColor fr = reflective_brdf->sample_f( sr, wo, wi );    // computes wi
  Ray      reflected_ray( sr.hit_point, wi );

  if ( specular_btdf ) {
    L += sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 );
  } else {    // kr = 1.0
    Vector3D wt;
    RGBColor ft = specular_btdf->sample_f( sr, wo, wt );    // computes wt
    Ray      transmutted_ray( sr.hit_point, wt );

    L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * std::fabs( sr.normal.dot( wi ) );
    L += ft * sr.w.tracer_ptr->trace_ray( transmutted_ray, sr.depth + 1 ) * std::fabs( sr.normal.dot( wt ) );
  }
  return L;
}
