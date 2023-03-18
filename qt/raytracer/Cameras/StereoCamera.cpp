#include "StereoCamera.h"
#include "Utilities/Constants.h"
#include "World/ViewPlane.h"
#include "Utilities/Ray.h"
#include "World/World.h"
#include <cmath>

StereoCamera::StereoCamera() :
    Camera(), viewing( parallel ), pixel_gap( 5 ), beta( 0.75 ),    // in degrees;
    left_camera_ptr( nullptr ), right_camera_ptr( nullptr ) {}

StereoCamera::StereoCamera( const StereoCamera &other ) : StereoCamera() { copy( other ); }

StereoCamera &StereoCamera::operator=( const StereoCamera &other ) {
  if ( this == &other ) { copy( other ); }
  return *this;
}

void StereoCamera::copy( const StereoCamera &other ) {
  Camera::operator=( other );

  viewing          = other.viewing;
  pixel_gap        = other.pixel_gap;
  beta             = other.beta;    // in degrees;
  left_camera_ptr  = other.left_camera_ptr->clone();
  right_camera_ptr = other.right_camera_ptr->clone();
}

StereoCamera::~StereoCamera( void ) {
  if ( right_camera_ptr ) { delete right_camera_ptr; }
  if ( left_camera_ptr ) { delete left_camera_ptr; }
}

StereoCamera *StereoCamera::clone( void ) const { return new StereoCamera( *this ); }

void StereoCamera::setup_cameras() {
  double r = eye.distance( lookat );
  double x = r * std::tan( 0.5 * beta * PI_ON_180 );    // half the camera separation

  left_camera_ptr->set_eye( eye - x * u );
  left_camera_ptr->set_lookat( lookat - x * u );
  left_camera_ptr->compute_uvw();

  right_camera_ptr->set_eye( eye + x * u );
  right_camera_ptr->set_lookat( lookat + x * u );
  right_camera_ptr->compute_uvw();
}

//void StereoCamera::render_scene(const World& w) {
void StereoCamera::render_scene( const World &w, float, int ) {
  qDebug( "entering stereocamera_renderscene()\n" );

  ViewPlane vp   = w.vp;
  int       hres = vp.hres;

  //  w.open_window(2 * hres + pixel_gap, vres);

  double r = eye.distance( lookat );
  double x = r * std::tan( 0.5 * beta * PI_ON_180 );

  if ( viewing == parallel ) {
    qDebug( "render parallel\n" );
    qDebug( "rendering left camera\n" );
    left_camera_ptr->render_stereo( w, x, 0 );
    qDebug( "rendering right camera\n" );
    right_camera_ptr->render_stereo( w, -x, hres + pixel_gap );
  }

  if ( viewing == transverse ) {
    qDebug( "render transverse\n" );
    qDebug( "rendering right camera %.2f: \n", -x );
    right_camera_ptr->render_stereo( w, -x, 0 );
    qDebug( "rendering left camera %.2f, %d\n", x, hres + pixel_gap );
    left_camera_ptr->render_stereo( w, x, hres + pixel_gap );
  }
}
