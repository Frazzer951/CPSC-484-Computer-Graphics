#ifndef __DIELECTRIC__
#  define __DIELECTRIC__

#  include "Phong.h"
#  include "FresnelReflector.h"
#  include "FresnelTransmitter.h"

class Dielectric : public Phong {
public:
  Dielectric( void );
  Dielectric( const Dielectric &other );
  Dielectric         &operator=( const Dielectric &other );
  virtual Dielectric *clone( void ) const;
  virtual ~Dielectric( void );

  virtual RGBColor shade( ShadeRec &s );

private:
  void copy( const Dielectric &other );

  RGBColor cf_in;     // interior filter color
  RGBColor cf_out;    // exterior filter color

  FresnelReflector   *fresnel_brdf;
  FresnelTransmitter *fresnel_btdf;
};
