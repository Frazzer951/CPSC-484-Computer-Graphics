#include "PointLight.h"

PointLight::PointLight() : Light(), ls( 1.0 ), color( 1.0 ), location( 0, 1, 0 ) { set_shadows( true ); }

PointLight::PointLight( const PointLight &pl ) : PointLight() { copy( pl ); }

PointLight &PointLight::operator=( const PointLight &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void PointLight::copy( const PointLight &other ) {
  Light::operator=( other );
  ls       = other.ls;
  color    = other.color;
  location = other.location;
  set_shadows( other.cast_shadows() );
}

PointLight::~PointLight() {}

PointLight *PointLight::clone() const { return new PointLight( *this ); }

void PointLight::scale_radiance( const float b ) { ls = b; }

void PointLight::set_location( Vector3D d ) {
  location = d;
  location.normalize();
}
void PointLight::set_location( float dx, float dy, float dz ) {
  location.x = dx;
  location.y = dy;
  location.z = dz;
  location.normalize();
}

Vector3D PointLight::get_direction( ShadeRec &sr ) { return ( ( location - sr.hit_point ).hat() ); }

bool PointLight::in_shadow( const Ray &ray, const ShadeRec &sr ) const {
  double  t;
  int     num_objects = sr.w.objects.size();
  Point3D pt          = Point3D( location.x, location.y, location.z );    // translation required to Point3D; not in orig code
  double  d           = pt.distance( ray.o );
  //    float d = location.distance(ray.o);

  for ( int j = 0; j < num_objects; ++j ) {
    if ( sr.w.objects[j]->shadow_hit( ray, t ) && t < d ) { return true; }
  }
  return false;
}

//bool
//PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
//	float t;
//	int numObjects = sr.w.objects.size();
//	float d = location.distance(ray.o);

//	for (int j = 0; j < num_objects; j++)
//		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
//			return (true);

//	return (false);
//}

RGBColor PointLight::L( ShadeRec & ) { return ( ls * color ); }
