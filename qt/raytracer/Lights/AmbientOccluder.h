#ifndef __AMBIENT_OCCLUDER__
#define __AMBIENT_OCCLUDER__

#include "Light.h"
#include "Samplers/Sampler.h"
#include "Ambient.h"

class AmbientOccluder : public Light {
public:
  AmbientOccluder( void );

  AmbientOccluder( const Ambient &a );
  AmbientOccluder &operator=( const AmbientOccluder &rhs );
  virtual ~AmbientOccluder();

  virtual AmbientOccluder *clone() const;

  void set_sampler( Sampler *s_ptr );

  virtual Vector3D get_direction( ShadeRec &sr );

  virtual bool in_shadow( const Ray &ray, const ShadeRec &sr ) const;

  virtual RGBColor L( ShadeRec &sr );

private:
  void copy( const AmbientOccluder &other );

  float    ls;
  RGBColor color;
  float    min_amount;
  Vector3D u, v, w;

  Sampler *sampler_ptr;
  //  std::shared_ptr<Sampler>	sampler_ptr;
};

#endif    // __AMBIENT_OCCLUDER__
