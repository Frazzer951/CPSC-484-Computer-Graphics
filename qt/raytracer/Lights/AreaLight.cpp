// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "AreaLight.h"

GeometricObject *object_ptr;
Material        *material_ptr;
//    std::shared_ptr<Material> 	material_ptr;	 // will be an emissive material
Point3D          sample_point;
Normal           light_normal;    // assigned in get_direction - which therefore can't be const for any light
Vector3D         wi;              // unit direction from hit point being shaded to sample point on light surface

// ---------------------------------------------------------------- default constructor

AreaLight::AreaLight( void ) : Light(), object_ptr( nullptr ), material_ptr( nullptr ) { set_shadows( true ); }

AreaLight::AreaLight( const AreaLight &other ) : AreaLight() { copy( other ); }

AreaLight &AreaLight::operator=( const AreaLight &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void AreaLight::copy( const AreaLight &other ) {
  Light::operator=( other );

  GeometricObject *pgeo = other.object_ptr;
  object_ptr            = pgeo ? pgeo->clone() : NULL;

  //    Material* pmat = other.material_ptr;
  std::shared_ptr<Material> pmat = other.material_ptr;
  //    material_ptr = pmat ? pmat->clone() : NULL;
  material_ptr                   = pmat ? pmat : NULL;

  sample_point = other.sample_point;
  light_normal = other.light_normal;
  wi           = other.wi;
  set_shadows( other.cast_shadows() );
}

AreaLight::~AreaLight( void ) {
  if ( object_ptr ) { delete object_ptr; }
  //    if (material_ptr) { delete material_ptr; }    // delete if not shared_ptr
}

// ---------------------------------------------------------------- clone

AreaLight *AreaLight::clone( void ) const { return ( new AreaLight( *this ) ); }
// ---------------------------------------------------------------- destructor

// --------------------------------------------------------------- get_direction

Vector3D AreaLight::get_direction( ShadeRec &sr ) {
  sample_point = object_ptr->sample();    // used in the G function
  light_normal = object_ptr->get_normal( sample_point );
  wi           = sample_point - sr.hit_point;    // used in the G function
  wi.normalize();

  return ( wi );
}
// --------------------------------------------------------------- L

RGBColor AreaLight::L( ShadeRec &sr ) {
  float ndotd = -light_normal.dot( wi );
  if ( ndotd > 0.0 ) {
    return ( material_ptr->get_Le( sr ) );
  } else {
    return ( black );
  }
}
// ---------------------------------------------------------------- in_shadow

bool AreaLight::in_shadow( const Ray &ray, const ShadeRec &sr ) const {
  double t;
  int    num_objects = sr.w.objects.size();
  float  ts          = ( sample_point - ray.o ).dot( ray.d );

  for ( int j = 0; j < num_objects; j++ ) {
    if ( sr.w.objects[j]->shadow_hit( ray, t ) && t < ts ) { return ( true ); }
  }
  return ( false );
}

// ---------------------------------------------------------------- G
// G is part of the geometric factor

float AreaLight::G( const ShadeRec &sr ) const {
  float ndotd = -light_normal.dot( wi );
  float d2    = sample_point.d_squared( sr.hit_point );
  return ( ndotd / d2 );
}
// ---------------------------------------------------------------- pdf

float AreaLight::pdf( ShadeRec &sr ) const { return ( object_ptr->pdf( sr ) ); }
