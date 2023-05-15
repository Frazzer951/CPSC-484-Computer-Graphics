#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/Point3D.h"
#include "Utilities/Normal.h"
#include "Lights/Light.h"
#include "Materials/Material.h"
#include "GeometricObjects/GeometricObject.h"

class EnvironmentLight : public Light {
public:
  EnvironmentLight( void );
  EnvironmentLight( const EnvironmentLight &other );
  EnvironmentLight &operator=( const EnvironmentLight &other );
  virtual ~EnvironmentLight();
  virtual EnvironmentLight *clone() const;

  // TODO...
  void             set_sampler( Sampler *sampler );
  virtual Vector3D get_direction( ShadeRec &s );

  virtual RGBColor L( ShadeRec &sr );

  virtual bool in_shadow( const Ray &ray, const ShadeRec &sr ) const;

  virtual float pdf( const ShadeRec &sr ) const;

  void set_material( std::shared_ptr<Material> material );

private:
  void copy( const EnvironmentLight &other );

  Sampler                  *sampler_ptr;
  //    Material* material_ptr;
  std::shared_ptr<Material> material_ptr;
  Vector3D                  u, v, w;
  Vector3D                  wi;
};
