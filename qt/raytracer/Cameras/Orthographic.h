#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

#include "Camera.h"
#include "Utilities/Point2D.h"

class Orthographic : public Camera {
public:
  Orthographic();
  Orthographic( const Orthographic &other );
  virtual Camera *clone( void ) const;
  Orthographic   &operator=( const Orthographic &other );
  virtual ~Orthographic();

  void compute_direction( void );
  void compute_distance( void );

  //  virtual void render_scene(const World& w);
  virtual void render_scene( const World &w, float x = 0.0, int offset = 0 );

private:
  void copy( const Orthographic &other );

  float    d;
  Vector3D dir;
};

#endif    // ORTHOGRAPHIC_H
