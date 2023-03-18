#ifndef __BBOX__
#define __BBOX__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Ray.h"
#include "Point3D.h"

struct BBox {
public:
  BBox( void );
  BBox( double x0, double x1, double y0, double y1, double z0, double z1 );

  BBox( const Point3D p0, const Point3D p1 );
  BBox( const BBox &bbox );
  BBox &operator=( const BBox &rhs );
  ~BBox( void );

  bool hit( const Ray &ray ) const;

  bool inside( const Point3D &p ) const;

  double x0, x1, y0, y1, z0, z1;

private:
  void copy( const BBox &other );
};

#endif
