#include "EnvironmentLight.h"

EnvironmentLight::EnvironmentLight( void ) : Light(), material_ptr( nullptr ) {}

EnvironmentLight::EnvironmentLight( const EnvironmentLight &other ) : EnvironmentLight() { copy( other ); }

EnvironmentLight &EnvironmentLight::operator=( const EnvironmentLight &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void EnvironmentLight::copy( const EnvironmentLight &other ) {
  Light::operator=( other );

  Sampler *psamp = other.sampler_ptr;
  //    Material* pmat = other.material_ptr;

  sampler_ptr  = psamp ? psamp->clone() : NULL;
  //    material_ptr = pmat ? pmat->clone() : NULL;
  material_ptr = other.material_ptr;

  set_shadows( other.cast_shadows() );
}

EnvironmentLight::~EnvironmentLight() {}

EnvironmentLight *EnvironmentLight::clone() const { return new EnvironmentLight( *this ); }

void EnvironmentLight::set_sampler( Sampler *sampler ) { sampler_ptr = sampler; }

Vector3D EnvironmentLight::get_direction( ShadeRec &sr ) {
  w = sr.normal;
  v = Vector3D( 0.0034, 1, 0.0071 ).cross( w );
  v.normalize();
  u          = v.cross( w );
  Point3D sp = sampler_ptr->sample_hemisphere();
  wi         = sp.x * u + sp.y * v + sp.z * w;
  return wi;    // TODO: check
}

void EnvironmentLight::set_material( std::shared_ptr<Material> material ) { material_ptr = material; }

// TODO: check against text
bool EnvironmentLight::in_shadow( const Ray &ray, const ShadeRec &sr ) const {
  double t;
  int    num_objects = sr.w.objects.size();

  for ( int j = 0; j < num_objects; j++ ) {
    if ( sr.w.objects[j]->shadow_hit( ray, t ) ) return true;
  }
  return false;
}

//Vector3D    TODO: class
//FakeSphericalLight::get_direction(ShadeRec& sr) {

//	float r = 3.0;
//	Point3D new_location;
//	new_location.x = location.x + r * (2.0 * rand_float() - 1.0);
//	new_location.y = location.y + r * (2.0 * rand_float() - 1.0);
//	new_location.z = location.z + r * (2.0 * rand_float() - 1.0);

//	return((new_location - sr.hit_point).hat());
//}

RGBColor EnvironmentLight::L( ShadeRec &sr ) { return material_ptr->get_Le( sr ); }

float EnvironmentLight::pdf( const ShadeRec &sr ) const { return sr.normal.dot( wi ) * invPI; }
