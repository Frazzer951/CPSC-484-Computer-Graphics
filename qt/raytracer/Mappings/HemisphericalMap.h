#ifndef __HEMISPHERICAL_MAP__
#define __HEMISPHERICAL_MAP__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the definition of the class HemisphericalMap
// This class inherits from Mapping, and defines a default spherical mapping
// Here, an image with an aspect ratio of 2:1 is mapped onto a sphere so
// that it just covers the whole sphere

#include "Mapping.h"
#include "Utilities/Constants.h"

class HemisphericalMap : public Mapping {
public:
  HemisphericalMap( void );
  HemisphericalMap( const HemisphericalMap &sm );

  HemisphericalMap &operator=( const HemisphericalMap &rhs );

  virtual HemisphericalMap *clone( void ) const;
  ~HemisphericalMap( void );

  virtual void get_texel_coordinates( const Point3D &local_hit_point, const int xres, const int yres, int &row,
                                      int &column ) const;
};

#endif