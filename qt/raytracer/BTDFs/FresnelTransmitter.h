#ifndef __FRESNEL_TRANSMITTER__
#define __FRESNEL_TRANSMITTER__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// FresnelTransmitter is the base class for the FresnelTransmitters
// we need a sampler here, because even a Matte material needs to call sample_f with a
// cosine distribution for path shading.

//#include <math.h>

#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"
#include "Samplers/Sampler.h"
#include "BTDFs/BTDF.h"

class FresnelTransmitter : public BTDF {
public:
  FresnelTransmitter( void );

  virtual FresnelTransmitter *clone( void ) const = 0;

  FresnelTransmitter( const FresnelTransmitter &FresnelTransmitter );
  FresnelTransmitter &operator=( const FresnelTransmitter &rhs );

  virtual ~FresnelTransmitter( void );

  void set_sampler( Sampler *sPtr );

  virtual RGBColor f( const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi ) const              = 0;
  virtual RGBColor sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wi ) const             = 0;
  virtual RGBColor sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wi, float &pdf ) const = 0;
  virtual RGBColor rho( const ShadeRec &sr, const Vector3D &wo ) const                                = 0;
  virtual RGBColor tir( const ShadeRec &sr, const Vector3D &wo ) const                                = 0;
  virtual RGBColor fresnel( const ShadeRec &sr, const Vector3D &wo ) const                            = 0;

protected:
  Sampler *sampler_ptr;    // for indirect illumination
  int      eta_in;         // TODO
  int      eta_out;        // TODO
};

#endif
