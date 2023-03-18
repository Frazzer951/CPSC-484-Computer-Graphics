#include "AmbientOccluder.h"
#include "Utilities/ShadeRec.h"
#include "World/World.h"

AmbientOccluder::AmbientOccluder( void ) :
    Light(), ls( 1.0 ), color( 1.0 ), min_amount( 0.0 ), u( 0, 0, 1 ), v( 1, 0, 0 ), w( 0, 1, 0 ),

    sampler_ptr( nullptr ) {}

AmbientOccluder::AmbientOccluder( const Ambient &other ) : AmbientOccluder() { copy( other ); }

AmbientOccluder &AmbientOccluder::operator=( const AmbientOccluder &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void AmbientOccluder::copy( const AmbientOccluder &other ) {
  Light::operator=( other );

  ls         = other.ls;
  color      = other.color;
  min_amount = other.min_amount;
  u          = other.u;
  v          = other.v;
  w          = other.w;

  Sampler *psamp = other.sampler_ptr;
  sampler_ptr    = psamp ? psamp->clone() : NULL;

  //    sampler_ptr = std::shared_ptr<Sampler>(rhs.sampler_ptr);
}

AmbientOccluder::~AmbientOccluder() {
  if ( sampler_ptr ) { delete sampler_ptr; }
}

AmbientOccluder *AmbientOccluder::clone() const { return new AmbientOccluder( *this ); }

void AmbientOccluder::set_sampler( Sampler *s_ptr ) {
  if ( sampler_ptr ) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
  if ( s_ptr ) {
    sampler_ptr = s_ptr->clone();
    sampler_ptr->map_samples_to_hemisphere( 1 );
  }
  //    sampler_ptr.reset(s_ptr);
}

Vector3D AmbientOccluder::get_direction( ShadeRec & ) {
  Point3D sp = sampler_ptr->sample_hemisphere();
  return ( sp.x * u + sp.y * v + sp.z * w );
}

bool AmbientOccluder::in_shadow( const Ray &ray, const ShadeRec &sr ) const {
  double t;
  int    num_objects = sr.w.objects.size();

  for ( int j = 0; j < num_objects; j++ ) {
    if ( sr.w.objects[j]->shadow_hit( ray, t ) ) { return ( true ); }
  }
  return ( false );
}

RGBColor AmbientOccluder::L( ShadeRec &sr ) {
  w = sr.normal;
  v = w.cross( Vector3D( 0.0072, 1.0, 0.0034 ) );    // jitter the up vector in case normal is vertical
  v.normalize();
  u = v.cross( w );

  Ray shadow_ray;
  shadow_ray.o = sr.hit_point;
  shadow_ray.d = get_direction( sr );

  if ( in_shadow( shadow_ray, sr ) ) {
    return ( min_amount * ls * color );
  } else {
    return ( ls * color );
  }
}
