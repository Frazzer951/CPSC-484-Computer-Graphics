#ifndef FISHEYE_H
#define FISHEYE_H

#include "Camera.h"
#include "Utilities/Point2D.h"

class Fisheye : public Camera {
public:
  Fisheye( void );
  Fisheye( const Fisheye &other );
  Fisheye         &operator=( const Fisheye &other );
  virtual Fisheye *clone( void ) const;
  virtual ~Fisheye();

  Vector3D     ray_direction( const Point2D &pp, const int hres, const int vres, const float s, float &r_squared );
  //    virtual void render_scene(const World& w);
  virtual void render_scene( const World &w, float x = 0.0, int offset = 0 );

  void set_fov( float psi );
  void set_rectangular( bool r );

private:
  void copy( const Fisheye &other );

  float psi_max;        // in degrees
  bool  rectangular;    // render corners or not
};

inline void Fisheye::set_fov( float psi ) { psi_max = 0.5 * psi; }

inline void Fisheye::set_rectangular( bool r ) { rectangular = r; }

#endif    // FISHEYE_H
