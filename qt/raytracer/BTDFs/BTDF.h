#ifndef __BTDF__
#define __BTDF__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// BTDF is the base class for the BTDFs
// we need a sampler here, because even a Matte material needs to call sample_f with a
// cosine distribution for path shading.

//#include <math.h>

#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"
#include "Samplers/Sampler.h"

class BTDF {
public:
  BTDF( void );
  BTDF( const BTDF &BTDF );
  BTDF &operator=( const BTDF &other );
  virtual ~BTDF( void );
  virtual BTDF *clone( void ) const = 0;

  void set_sampler( Sampler *sPtr );

  virtual RGBColor f( const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi ) const;
  virtual RGBColor sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wi ) const;
  virtual RGBColor rho( const ShadeRec &sr, const Vector3D &wo ) const = 0;

private:
  void copy( const BTDF &other );

protected:
  Sampler *sampler_ptr;    // for indirect illumination
};

#endif
