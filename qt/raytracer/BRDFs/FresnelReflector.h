
#ifndef __FRESNEL_REFLECTOR__
#define __FRESNEL_REFLECTOR__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This implements a perfect diffuse scatterer

#include "BRDF.h"

class FresnelReflector : public BRDF {
public:
  FresnelReflector( void );
  FresnelReflector( const FresnelReflector &other );
  FresnelReflector &operator=( const FresnelReflector &other );
  virtual ~FresnelReflector( void );
  virtual FresnelReflector *clone( void ) const;

  virtual RGBColor f( const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi ) const;
  virtual RGBColor sample_f( const ShadeRec &sr, const Vector3D &wo, Vector3D &wi, float &pdf ) const;

  virtual RGBColor rho( const ShadeRec &sr, const Vector3D &wo ) const;

  void set_ka( const float ka );
  void set_kd( const float kd );
  void set_cd( const RGBColor &c );

  void set_cd( const float r, const float g, const float b );
  void set_cd( const float c );

  float fresnel( const ShadeRec &sr ) const;

private:
  void copy( const FresnelReflector &other );

  float    kd;
  RGBColor cd;
};
// -------------------------------------------------------------- set_ka

inline void FresnelReflector::set_ka( const float k ) { kd = k; }
// -------------------------------------------------------------- set_kd

inline void FresnelReflector::set_kd( const float k ) { kd = k; }
// -------------------------------------------------------------- set_cd

inline void FresnelReflector::set_cd( const RGBColor &c ) { cd = c; }
// ---------------------------------------------------------------- set_cd

inline void FresnelReflector::set_cd( const float r, const float g, const float b ) {
  cd.r = r;
  cd.g = g;
  cd.b = b;
}
// ---------------------------------------------------------------- set_cd

inline void FresnelReflector::set_cd( const float c ) {
  cd.r = c;
  cd.g = c;
  cd.b = c;
}

#endif
