#include "Matte.h"

// ---------------------------------------------------------------- copy constructor
Matte::Matte() : Material(), ambient_brdf( new Lambertian ), diffuse_brdf( new Lambertian ) {}

Matte::Matte( const Matte &other ) : Matte() { copy( other ); }

Matte &Matte::operator=( const Matte &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Matte::copy( const Matte &other ) {
  Material::operator=( other );

  Lambertian *pamb  = other.ambient_brdf;
  Lambertian *pdiff = other.diffuse_brdf;

  ambient_brdf = pamb ? pamb->clone() : NULL;
  diffuse_brdf = pdiff ? pdiff->clone() : NULL;
}

// ---------------------------------------------------------------- destructor
Matte::~Matte( void ) {
  if ( ambient_brdf ) { delete ambient_brdf; }
  if ( diffuse_brdf ) { delete diffuse_brdf; }
}

Material *Matte::clone( void ) const { return ( new Matte( *this ) ); }

// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection
void Matte::set_ka( const float ka ) { ambient_brdf->set_kd( ka ); }

// this also sets Lambertian::kd, but for a different Lambertian object
void Matte::set_kd( const float kd ) { diffuse_brdf->set_kd( kd ); }

void Matte::set_cd( const RGBColor c ) {
  ambient_brdf->set_cd( c );
  diffuse_brdf->set_cd( c );
}
void Matte::set_cd( const float r, const float g, const float b ) {
  ambient_brdf->set_cd( r, g, b );
  diffuse_brdf->set_cd( r, g, b );
}
void Matte::set_cd( const float c ) {
  ambient_brdf->set_cd( c );
  diffuse_brdf->set_cd( c );
}

// ---------------------------------------------------------------- shade
RGBColor Matte::shade( ShadeRec &sr ) {
  Vector3D wo         = -sr.ray.d;
  RGBColor L          = ambient_brdf->rho( sr, wo ) * sr.w.ambient_ptr->L( sr );
  int      num_lights = (int) sr.w.lights.size();

  for ( int j = 0; j < num_lights; j++ ) {
    Vector3D wi     = sr.w.lights[j]->get_direction( sr );
    float    ndotwi = sr.normal.dot( wi );
    if ( ndotwi > 0.0 ) L += diffuse_brdf->f( sr, wo, wi ) * sr.w.lights[j]->L( sr ) * ndotwi;
  }
  return ( L );
}

RGBColor Matte::area_light_shade( ShadeRec &sr ) {
  Vector3D wo         = -sr.ray.d;
  RGBColor L          = ambient_brdf->rho( sr, wo ) * sr.w.ambient_ptr->L( sr );
  int      num_lights = sr.w.lights.size();

  for ( int j = 0; j < num_lights; j++ ) {
    Light   *light_ptr = sr.w.lights[j];
    Vector3D wi        = light_ptr->get_direction( sr );
    float    ndotwi    = sr.normal.dot( wi );

    if ( ndotwi > 0.0 ) {
      bool in_shadow = false;

      if ( light_ptr->cast_shadows() ) {
        Ray shadow_ray( sr.hit_point, wi );
        in_shadow = light_ptr->in_shadow( shadow_ray, sr );
      }

      if ( !in_shadow )
        L += diffuse_brdf->f( sr, wo, wi ) * light_ptr->L( sr ) * light_ptr->G( sr ) * ndotwi / light_ptr->pdf( sr );
    }
  }

  return ( L );
}
