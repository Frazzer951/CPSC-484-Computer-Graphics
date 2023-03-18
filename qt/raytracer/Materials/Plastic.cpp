#include "Plastic.h"

Plastic::Plastic( void ) :    // should be Phong ?
    Material(), ambient_brdf( new Lambertian ), diffuse_brdf( new Lambertian ), specular_brdf( new GlossySpecular ) {}

Plastic::Plastic( const Plastic &other ) : Plastic() { copy( other ); }

Plastic &Plastic::operator=( const Plastic &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Plastic::copy( const Plastic &other ) {
  Material::operator=( other );

  Lambertian     *pamb   = other.ambient_brdf;
  Lambertian     *pdiff  = other.diffuse_brdf;
  GlossySpecular *pgloss = other.specular_brdf;

  ambient_brdf  = pamb ? pamb->clone() : NULL;
  diffuse_brdf  = pdiff ? pdiff->clone() : NULL;
  specular_brdf = pgloss ? pgloss->clone() : NULL;
}

Plastic *Plastic::clone( void ) const { return new Plastic( *this ); }

Plastic::~Plastic( void ) {
  if ( ambient_brdf ) { delete ambient_brdf; }
  if ( diffuse_brdf ) { delete diffuse_brdf; }
  if ( specular_brdf ) { delete specular_brdf; }
}

RGBColor Plastic::shade( ShadeRec &sr ) {
  Vector3D wo         = -sr.ray.d;
  RGBColor L          = ambient_brdf->rho( sr, wo ) * sr.w.ambient_ptr->L( sr );
  int      num_lights = sr.w.lights.size();

  for ( int j = 0; j < num_lights; j++ ) {
    Vector3D wi     = sr.w.lights[j]->get_direction( sr );
    float    ndotwi = sr.normal.dot( wi );

    if ( ndotwi > 0.0 ) {
      bool in_shadow = false;

      if ( sr.w.lights[j]->cast_shadows() ) {
        Ray shadowsRay( sr.hit_point, wi );
        in_shadow = sr.w.lights[j]->in_shadow( shadowsRay, sr );
      }

      if ( !in_shadow )
        L += ( diffuse_brdf->f( sr, wo, wi ) + specular_brdf->f( sr, wo, wi ) ) * sr.w.lights[j]->L( sr ) * ndotwi;
    }
  }

  return L;
}
