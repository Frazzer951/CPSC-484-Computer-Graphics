#include "GlossyReflector.h"

// ---------------------------------------------------------------- default constructor

GlossyReflector::GlossyReflector( void ) : Phong(), glossy_specular_brdf( new GlossySpecular ) {}

GlossyReflector::GlossyReflector( const GlossyReflector &other ) : GlossyReflector() { copy( other ); }

GlossyReflector &GlossyReflector::operator=( const GlossyReflector &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void GlossyReflector::copy( const GlossyReflector &other ) {
  Phong::operator=( other );

  GlossySpecular *pgloss = other.specular_brdf;
  glossy_specular_brdf   = pgloss ? pgloss->clone() : NULL;
}

// ---------------------------------------------------------------- destructor
GlossyReflector::~GlossyReflector( void ) {
  if ( glossy_specular_brdf ) { delete glossy_specular_brdf; }
}

GlossyReflector *GlossyReflector::clone() const { return new GlossyReflector( *this ); }

RGBColor GlossyReflector::shade( ShadeRec &sr ) {
  RGBColor L( Phong::area_light_shade( sr ) );    // direct illumination
  Vector3D wo( -sr.ray.d );
  Vector3D wi;
  float    pdf;
  RGBColor fr( glossy_specular_brdf->sample_f( sr, wo, wi, pdf ) );
  Ray      reflected_ray( sr.hit_point, wi );

  L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * ( sr.normal.dot( wi ) ) / pdf;

  return ( L );
}

RGBColor GlossyReflector::area_light_shade( ShadeRec &sr ) {
  RGBColor L( Phong::area_light_shade( sr ) );    // direct illumination
  Vector3D wo( -sr.ray.d );
  Vector3D wi;
  float    pdf;
  RGBColor fr( glossy_specular_brdf->sample_f( sr, wo, wi, pdf ) );
  Ray      reflected_ray( sr.hit_point, wi );

  L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * ( sr.normal.dot( wi ) ) / pdf;

  return ( L );
}
