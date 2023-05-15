#include "Spherical.h"

#include "Utilities/RGBColor.h"
#include "World/World.h"
#include <cmath>
#include <random>

Spherical::Spherical() : Camera(), psi_max( 180 ), lambda_max( 180 ) {}

Spherical::Spherical( const Spherical &other ) : Spherical() { copy( other ); }

Spherical &Spherical::operator=( const Spherical &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Spherical::copy( const Spherical &other ) {
  Camera::operator=( other );

  psi_max    = other.psi_max;
  lambda_max = other.lambda_max;
}

Spherical *Spherical::clone( void ) const { return new Spherical( *this ); }

Spherical::~Spherical() {}

Vector3D Spherical::ray_direction( const Point2D &pp, const int hres, const int vres, const float s ) {
  // compute the normalized device coordinates

  Point2D pn( 2.0 / ( s * hres ) * pp.x, 2.0 / ( s * vres ) * pp.y );

  // compute the angles lambda and phi in radians

  float lambda = pn.x * lambda_max * PI_ON_180;
  float psi    = pn.y * psi_max * PI_ON_180;

  // compute the spherical azimuth and polar angles

  float phi   = PI - lambda;
  float theta = 0.5 * PI - psi;

  float sin_theta = std::sin( theta );
  float sin_phi   = std::sin( phi );
  float cos_theta = std::cos( theta );
  float cos_phi   = std::cos( phi );

  Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;

  return dir;
}

//void Spherical::render_scene(const World& w) {
void Spherical::render_scene( const World &w, float x, int offset ) {
  RGBColor  L;
  ViewPlane vp( w.vp );
  int       hres = vp.hres;
  int       vres = vp.vres;
  float     s    = vp.s;
  Ray       ray;
  int       depth = 0;
  Point2D   sp;    // sample point in [0, 1] x [0, 1]
  Point2D   pp;    // sample point on the pixel

  ray.o = eye;

  std::vector<Point2D> pixels;

  for ( int r = 0; r < vp.vres; r++ ) {      // up
    for ( int c = 0; c < vp.hres; c++ ) {    // across
      pixels.push_back( Point2D( r, c ) );
    }
  }
  std::mt19937_64 mersenne_generator;    // 64-bit mersenne random generator
  std::shuffle( pixels.begin(), pixels.end(), mersenne_generator );

  for ( int r = 0; r < vres; r++ ) {      // up
    for ( int c = 0; c < hres; c++ ) {    // accross
      L = black;

      for ( int j = 0; j < vp.num_samples; j++ ) {
        sp    = vp.sampler_ptr->sample_unit_square();
        pp.x  = s * ( c - 0.5 * hres + sp.x ) + x;
        pp.y  = s * ( r - 0.5 * vres + sp.y );
        ray.d = ray_direction( pp, hres, vres, s );

        L += w.tracer_ptr->trace_ray( ray, depth );
      }

      L /= vp.num_samples;
      L *= exposure_time;
      w.display_pixel( r, c + offset, L );
    }
  }
}
