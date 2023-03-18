#ifndef SPHERICAL_H
#define SPHERICAL_H

#include "Camera.h"
#include "Utilities/Point2D.h"

class Spherical : public Camera {
public:
  Spherical( void );
  Spherical( const Spherical &s );
  Spherical         &operator=( const Spherical &rhs );
  virtual Spherical *clone( void ) const;
  virtual ~Spherical( void );

  Vector3D     ray_direction( const Point2D &pp, const int hres, const int vres, const float s );
  //  virtual void render_scene(const World& w);
  virtual void render_scene( const World &w, float x = 0.0, int offset = 0 );

  void set_horizontal_fov( float hfov );
  void set_vertical_fov( float vfov );

private:
  void copy( const Spherical &other );

  float psi_max;       // in degrees
  float lambda_max;    // in degrees
};

inline void Spherical::set_horizontal_fov( float hfov ) { lambda_max = 0.5 * hfov; }

inline void Spherical::set_vertical_fov( float vfov ) { psi_max = 0.5 * vfov; }

#endif    // SPHERICAL_H
