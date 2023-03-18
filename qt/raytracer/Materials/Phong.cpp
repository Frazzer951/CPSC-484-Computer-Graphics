#include "Phong.h"

Phong::Phong( void ) :
    Material(), ambient_brdf( new Lambertian ), diffuse_brdf( new Lambertian ), specular_brdf( new GlossySpecular ) {}

Phong::Phong( const Phong &other ) : Phong() { copy( other ); }

Phong &Phong::operator=( const Phong &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Phong::copy( const Phong &other ) {
  Material::operator=( other );

  Lambertian     *pamb   = other.ambient_brdf;
  Lambertian     *pdiff  = other.diffuse_brdf;
  GlossySpecular *pgloss = other.specular_brdf;

  ambient_brdf  = pamb ? pamb->clone() : NULL;
  diffuse_brdf  = pdiff ? pdiff->clone() : NULL;
  specular_brdf = pgloss ? pgloss->clone() : NULL;
}

Phong::~Phong() {
  if ( ambient_brdf ) { delete ambient_brdf; }
  if ( diffuse_brdf ) { delete diffuse_brdf; }
  if ( specular_brdf ) { delete specular_brdf; }
}

Phong *Phong::clone() const { return new Phong( *this ); }

// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection
void Phong::set_ka( const float ka ) { ambient_brdf->set_kd( ka ); }

// this also sets Lambertian::kd, but for a different Lambertian object
void Phong::set_kd( const float kd ) { diffuse_brdf->set_kd( kd ); }

void Phong::set_cd( const RGBColor c ) {
  ambient_brdf->set_cd( c );
  diffuse_brdf->set_cd( c );
}
void Phong::set_cd( const float r, const float g, const float b ) {
  ambient_brdf->set_cd( r, g, b );
  diffuse_brdf->set_cd( r, g, b );
}
void Phong::set_cd( const float c ) {
  ambient_brdf->set_cd( c );
  diffuse_brdf->set_cd( c );
}

void Phong::set_ks( const float ks ) { specular_brdf->set_ks( ks ); }

void Phong::set_exp( const float exp ) { specular_brdf->set_exp( exp ); }

void Phong::set_cs( const RGBColor &c ) { specular_brdf->set_cs( c ); }
void Phong::set_cs( const float r, const float g, const float b ) { specular_brdf->set_cs( r, g, b ); }
void Phong::set_cs( const float c ) { specular_brdf->set_cs( c ); }

RGBColor Phong::shade( ShadeRec &sr ) {
  Vector3D wo         = -sr.ray.d;
  RGBColor L          = ambient_brdf->rho( sr, wo ) * sr.w.ambient_ptr->L( sr );
  int      num_lights = sr.w.lights.size();

  for ( int j = 0; j < num_lights; j++ ) {
    Vector3D wi     = sr.w.lights[j]->get_direction( sr );
    float    ndotwi = sr.normal.dot( wi );

    if ( ndotwi > 0.0 ) {
      bool in_shadow = false;

      if ( sr.w.lights[j]->cast_shadows() ) {
        Ray shadowRay( sr.hit_point, wi );
        in_shadow = sr.w.lights[j]->in_shadow( shadowRay, sr );
      }

      if ( !in_shadow ) {
        L += ( diffuse_brdf->f( sr, wo, wi ) + specular_brdf->f( sr, wo, wi ) ) * sr.w.lights[j]->L( sr ) * ndotwi;
        sr.w.lights[j]->L( sr ) * ndotwi;
      }
    }
  }
  return ( L );
}
