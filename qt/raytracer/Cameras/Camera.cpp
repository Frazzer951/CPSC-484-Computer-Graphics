#include "Cameras/Camera.h"

// ----------------------------------------------------------------- default constructor

Camera::Camera() :
    eye( 0, 0, 500 ), lookat( 0 ), ra( 0 ), u( 1, 0, 0 ), v( 0, 1, 0 ), w( 0, 0, 1 ), up( 0, 1, 0 ), exposure_time( 1.0 ) {}

// ----------------------------------------------------------------- copy constructor
Camera::Camera( const Camera &other ) : Camera() { copy( other ); }

Camera &Camera::operator=( const Camera &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void Camera::copy( const Camera &other ) {
  eye           = other.eye;
  lookat        = other.lookat;
  ra            = other.ra;
  u             = other.u;
  v             = other.v;
  w             = other.w;
  up            = other.up;
  exposure_time = other.exposure_time;
}

Camera::~Camera() {}

//-------------------------------------------------------------- compute_uvw
// This computes an orthornormal basis given the view point, lookat point, and up vector
void Camera::compute_uvw( void ) {
  w = eye - lookat;
  w.normalize();
  u = up.cross( w );
  u.normalize();
  v = w.cross( u );

  // take care of the singularity by hardwiring in specific camera orientations

  if ( eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y ) {    // camera looking vertically down
    u = Vector3D( 0, 0, 1 );
    v = Vector3D( 1, 0, 0 );
    w = Vector3D( 0, 1, 0 );
  }

  if ( eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y ) {    // camera looking vertically up
    u = Vector3D( 1, 0, 0 );
    v = Vector3D( 0, 0, 1 );
    w = Vector3D( 0, -1, 0 );
  }
}
