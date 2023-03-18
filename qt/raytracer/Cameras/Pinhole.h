#ifndef __PINHOLE__
#define __PINHOLE__

#include "Utilities/Point2D.h"
#include "World/World.h"    // we can #include "World.h" here
#include "Cameras/Camera.h"

//=====================================
// Pinhole
//=====================================
//
class Pinhole : public Camera {
public:
  Pinhole();
  Pinhole( const Pinhole &other );
  Pinhole &operator=( const Pinhole &other );
  virtual ~Pinhole();
  virtual Camera *clone() const;

  void     set_view_distance( const float vpd );
  void     set_zoom( const float zoom_factor );
  Vector3D get_direction( const Point2D &p ) const;

  virtual void render_scene( const World &w, float x = 0.0, int offset = 0 );

private:
  void copy( const Pinhole &other );

  float d;       // view plane distance
  float zoom;    // zoom factor
};

#endif
