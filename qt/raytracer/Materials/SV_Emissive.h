#ifndef SV_EMISSIVE_HXX
#define SV_EMISSIVE_HXX

#include "Material.h"
#include "Textures/Texture.h"

class SV_Emissive : public Material {
public:
  SV_Emissive( void );
  SV_Emissive( const SV_Emissive &e );
  SV_Emissive         &operator=( const SV_Emissive &rhs );
  virtual SV_Emissive *clone( void ) const;
  virtual ~SV_Emissive( void );

  void scale_radiance( const float _ls );
  void set_ce( Texture *t_ptr );

  virtual RGBColor get_Le( ShadeRec &sr ) const;
  virtual RGBColor shade( ShadeRec &sr );
  virtual RGBColor area_light_shade( ShadeRec &sr );

private:
  void copy( const SV_Emissive &other );

  float    ls;    // radiance scaling factor
  Texture *ce;    // color
};

inline void SV_Emissive::scale_radiance( const float _ls ) { ls = _ls; }

inline void SV_Emissive::set_ce( Texture *t_ptr ) {
  delete ce;
  ce = t_ptr;
}

#endif    // SV_EMISSIVE_HXX
