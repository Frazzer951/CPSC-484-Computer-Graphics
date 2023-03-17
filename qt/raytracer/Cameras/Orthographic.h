#ifndef __ORTHOGRAPHIC__
#define __ORTHOGRAPHIC__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Utilities/Point2D.h"
#include "World/World.h"    // we can #include "World.h" here

class Orthographic : public Camera {
public:
  Orthographic();
  //  Orthographic(const Pinhole& ph);
  //  virtual Camera* clone(void) const;
  //  Orthographic&
  //  operator= (const Pinhole& rhs);
  //  virtual ~Orthographic();

  void set_view_distance( const float vpd );
  void set_zoom( const float zoom_factor );

  //  Vector3D get_direction(const Point2D& p) const;
  virtual void render_scene( const World &w );

private:
  float d;       // view plane distance
  float zoom;    // zoom factor
};

//-------------------------------------------------------------------------- set_vpd
inline void Orthographic::set_view_distance( float _d ) { d = _d; }
//-------------------------------------------------------------------------- set_zoom
inline void Orthographic::set_zoom( float zoom_factor ) { zoom = zoom_factor; }

#endif
