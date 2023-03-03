// This builds a scene that consists of 35 shaded spheres and a plane.
// The objects are illuminated by a directional light and rendered with
// ambient and diffuse shading.
// Perspective viewing is used with a pinhole camera.
// Jittered sampling for antialiasing is hardwired into the PinHole::render_scene function.
// There are no sampler classes in this project.
// These are in the Chapter 5 download file.
// The spheres are the same as those in the Chapter 14 page one image.

#include "Cameras/Pinhole.h"
#include "GeometricObjects/Primitives/Plane.h"
#include "GeometricObjects/Primitives/Sphere.h"
#include "GeometricObjects/Primitives/Rect.h"
#include "GeometricObjects/Triangles/Triangle.h"
#include "GeometricObjects/BeveledObjects/BeveledBox.h"

#include "Textures/Checker3D.h"

#include "Lights/Directional.h"
#include "Materials/Matte.h"

#include "Tracers/SingleSphere.h"
#include "Tracers/MultipleObjects.h"
#include "Tracers/RayCast.h"

#include "Utilities/Constants.h"
#include "Utilities/Maths.h"
#include "Utilities/Normal.h"
#include "Utilities/Point3D.h"
#include "Utilities/RandomUtils.h"
#include "Utilities/ShadeRec.h"
#include "Utilities/Vector3D.h"

#include "Samplers/Jittered.h"

#include "World.h"

#include <iostream>

// colors
RGBColor yellow( 1, 1, 0 );
RGBColor brown( 0.71, 0.40, 0.16 );
RGBColor darkGreen( 0.0, 0.81, 0.41 );
RGBColor orange( 1, 0.75, 0 );
RGBColor darkOrange( 0.75, 0.5, 0 );
RGBColor green( 0, 0.6, 0.3 );
RGBColor lightGreen( 0.61, 0.71, 0.4 );
RGBColor darkYellow( 0.61, 0.61, 0 );
RGBColor lightPurple( 0.65, 0.3, 1 );
RGBColor darkPurple( 0.5, 0, 1 );
RGBColor grey( 0.25 );
RGBColor lightGrey( 0.7 );
RGBColor darkBlue( 0.0, 0.0, 1.0 );
RGBColor lightBlue( 0.7, 0.95, 1.0 );
RGBColor cyan( 0, 1, 1 );
RGBColor greenCyan( 0.2, 0.6, 0.45 );

// -------------------------------------------------------------------- default constructor

// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World() : background_color( black ), tracer_ptr( nullptr ), ambient_ptr( new Ambient ), camera_ptr( nullptr ) {
  //    qDebug() << __PRETTY_FUNCTION__;
}
//------------------------------------------------------------------ destructor
World::~World() {
  //    qDebug() << __PRETTY_FUNCTION__;

  if ( tracer_ptr ) {
    delete tracer_ptr;
    tracer_ptr = nullptr;
  }
  if ( ambient_ptr ) {
    delete ambient_ptr;
    ambient_ptr = nullptr;
  }
  if ( camera_ptr ) {
    delete camera_ptr;
    camera_ptr = nullptr;
  }
  delete_objects();
  delete_lights();
}
//------------------------------------------------------------------ render_scene
// This uses orthographic viewing along the zw axis
void World::render_scene() const {
  //    qDebug() << __PRETTY_FUNCTION__;
  RGBColor pixel_color;
  Ray      ray;
  int      hres = vp.hres;
  int      vres = vp.vres;
  //	float		s		= vp.s;
  float    zw   = 100.0;    // hardwired in

  int     n = (int) sqrt( (float) vp.num_samples );
  Point2D sp;    // sample point in [0, 1] x [0, 1]
  Point2D pp;    // sample point on a pixel

  //    open_window(vp.hres, vp.vres);

  ray.d = Vector3D( 0, 0, -1 );

  for ( int r = 0; r < vres; r++ ) {       // up
    for ( int c = 0; c <= hres; c++ ) {    // across
      pixel_color = black;

      for ( int p = 0; p < n; ++p ) {    // anti-aliasing code from ch. 4
        for ( int q = 0; q < n; ++q ) {
          qDebug() << "just BEFORE creating sp";
          sp = vp.sampler_ptr->sample_unit_square();
          qDebug() << "just after creating sp";
          //                    pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);   // regular sampling
          //                    pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);

          //                    pp.x = vp.s * (c - 0.5 * vp.hres + rand_int());  // random sampling
          //                    pp.y = vp.s * (r - 0.5 * vp.vres + rand_int());

          //                    pp.x = vp.s * (c - 0.5 * vp.hres + q + rand_int());  // jittered sampling
          //                    pp.y = vp.s * (r - 0.5 * vp.vres + p + rand_int());

          pp.x = vp.s * ( c - 0.5 * vp.hres + sp.x );    // jittered sampling
          pp.y = vp.s * ( r - 0.5 * vp.vres + sp.y );

          ray.o       = Point3D( pp.x, pp.y, zw );
          pixel_color += tracer_ptr->trace_ray( ray );
        }
      }
      pixel_color /= vp.num_samples;    // average the colors
      display_pixel( r, c, pixel_color );
    }
  }
}
//void
//World::render_perspective(void) const {
//    RGBColor  pixel_color;
//    Ray       ray;
//    int 	  hres 	= vp.hres;
//	int 	  vres 	= vp.vres;
//	float	  s		= vp.s;      // pixel size
//    Point3D eye = camera.eye;  // private
//    float d = camera.d;        // private

//    ray.o = Point3D(0.0, 0.0, eye);
//    for (int r = 0; r < vp.vres; ++r) {
//        for (int c = 0; c <= vp.hres; ++c) {
//            ray.d = Vector3D(s * (c - 0.5 * (hres - 1.0)),
//                             s * (r - 0.5 * (vres - 1.0)), -d);
//            ray.d.normalize();
//            pixel_color = tracer_ptr->trace_ray(ray);
//            display_pixel(r, c, pixel_color);
//        }
//    }
//}
// ------------------------------------------------------------------ clamp
RGBColor World::max_to_one( const RGBColor &c ) const {
  //    qDebug() << __PRETTY_FUNCTION__;
  float max_value = max( c.r, max( c.g, c.b ) );

  if ( max_value > 1.0 ) {
    return ( c / max_value );
  } else {
    return ( c );
  }
}
// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one
RGBColor World::clamp_to_color( const RGBColor &raw_color ) const {
  //    qDebug() << __PRETTY_FUNCTION__;
  RGBColor c( raw_color );

  if ( raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0 ) {
    c.r = 1.0;
    c.g = 0.0;
    c.b = 0.0;
  }
  return ( c );
}
// ---------------------------------------------------------------------------display_pixel
// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function
void World::display_pixel( const int row, const int column, const RGBColor &raw_color ) const {
  //    qDebug() << __PRETTY_FUNCTION__;
  RGBColor mapped_color;

  if ( vp.show_out_of_gamut )
    mapped_color = clamp_to_color( raw_color );
  else
    mapped_color = max_to_one( raw_color );

  if ( vp.gamma != 1.0 ) mapped_color = mapped_color.powc( vp.inv_gamma );

  //have to start from max y coordinate to convert to screen coordinates
  int x = column;
  int y = vp.vres - row - 1;

  //    qDebug() << __PRETTY_FUNCTION__;
  paintArea->setPixel( x, y, (int) ( mapped_color.r * 255 ), (int) ( mapped_color.g * 255 ), (int) ( mapped_color.b * 255 ) );
}
// ----------------------------------------------------------------------------- hit_objects
ShadeRec World::hit_objects( const Ray &ray ) {
  //    qDebug() << __PRETTY_FUNCTION__;

  ShadeRec sr( *this );
  double   t;
  Normal   normal;
  Point3D  local_hit_point;
  float    tmin        = kHugeValue;
  int      num_objects = (int) objects.size();

  for ( int j = 0; j < num_objects; j++ ) {
    if ( objects[j]->hit( ray, t, sr ) && ( t < tmin ) ) {
      sr.hit_an_object = true;
      tmin             = t;
      sr.material_ptr  = objects[j]->get_material();
      sr.hit_point     = ray.o + t * ray.d;
      normal           = sr.normal;
      local_hit_point  = sr.local_hit_point;
    }
  }
  if ( sr.hit_an_object ) {
    sr.t               = tmin;
    sr.normal          = normal;
    sr.local_hit_point = local_hit_point;
  }
  return ( sr );
}

//ShadeRec
//World::hit_bare_bones_objects(const Ray& ray) { // ONLY in chapter 3:  bare-bones ray tracing
//    //    qDebug() << __PRETTY_FUNCTION__;

//	ShadeRec	sr(*this);
//	double		t;
//	Normal normal;
//	Point3D local_hit_point;
//	float		tmin 			= kHugeValue;
//	int 		num_objects 	= (int)objects.size();

//    for (int j = 0; j < num_objects; j++) {
//		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
//			sr.hit_an_object	= true;
//			tmin 				= t;
//            sr.color            = objects[j]->get_color();
//		}
//    }
//    return (sr);
//}
//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty
void World::delete_objects() {
  //    qDebug() << __PRETTY_FUNCTION__;
  int num_objects = (int) objects.size();
  for ( int j = 0; j < num_objects; j++ ) {
    delete objects[j];
    objects[j] = nullptr;
  }
  objects.erase( objects.begin(), objects.end() );
}
//------------------------------------------------------------------ delete_lights
void World::delete_lights() {
  //    qDebug() << __PRETTY_FUNCTION__;
  int num_lights = (int) lights.size();

  for ( int j = 0; j < num_lights; j++ ) {
    delete lights[j];
    lights[j] = nullptr;
  }

  lights.erase( lights.begin(), lights.end() );
}

void World::set_material( GeometricObject *geo, RGBColor color ) {
  float ka = 0.25;
  float kd = 0.75;

  Matte *matte_ptr = new Matte();
  matte_ptr->set_ka( ka );
  matte_ptr->set_kd( kd );
  matte_ptr->set_cd( color );
  geo->set_material( matte_ptr );
}

void World::add_sphere_helper( RGBColor color, Point3D pt, double radius ) {
  Sphere *s = new Sphere( pt, radius );
  set_material( s, color );
  add_object( s );
}

void World::add_bb_helper( RGBColor color, Point3D p0, Point3D p1, double r ) {
  //    std::cout << "making bb from " << p0 << " to " << p1 << " in color " << color << "\n";
  //    std::flush(std::cout);
  BeveledBox *bb = new BeveledBox( p0, p1, r );
  set_material( bb, color );
  add_object( bb );
}

void World::add_bb_helper( RGBColor color, Point3D p0, double dx, double dy, double dz, double r ) {
  World::add_bb_helper( color, p0, Point3D( p0.x + dx, p0.y + dy, p0.z + dz ), r );
}

void World::add_rect_helper( RGBColor color, Point3D pt, Vector3D pt1, Vector3D pt2, Normal n ) {
  // front face: +ve z
  Rect *ff = new Rect( pt, pt1, pt2, n );
  set_material( ff, color );
  add_object( ff );
}

void World::add_triangle_helper( RGBColor color, Point3D pt0, Point3D pt1, Point3D pt2 ) {
  // front face: +ve z
  Triangle *t = new Triangle( pt0, pt1, pt2 );
  set_material( t, color );
  add_object( t );
}

void World::build_spheres( void ) {
  // spheres
  add_sphere_helper( yellow, Point3D( 5, 3, 0 ), 30 );
  add_sphere_helper( brown, Point3D( 45, -7, -60 ), 20 );
  add_sphere_helper( darkGreen, Point3D( 40, 43, -100 ), 17 );
  add_sphere_helper( orange, Point3D( -20, 28, -15 ), 20 );
  add_sphere_helper( green, Point3D( -25, -7, -35 ), 27 );    //  5

  add_sphere_helper( lightGreen, Point3D( 20, -27, -35 ), 25 );
  add_sphere_helper( green, Point3D( 35, 18, -35 ), 22 );
  add_sphere_helper( brown, Point3D( -57, -17, -50 ), 15 );
  add_sphere_helper( lightGreen, Point3D( -47, 16, -80 ), 23 );
  add_sphere_helper( darkGreen, Point3D( -15, -32, -60 ), 22 );    // 10

  add_sphere_helper( darkYellow, Point3D( -35, -37, -80 ), 22 );
  add_sphere_helper( darkYellow, Point3D( 10, 43, -80 ), 22 );
  add_sphere_helper( darkYellow, Point3D( 30, -7, -80 ), 10 );    // hidden
  add_sphere_helper( darkGreen, Point3D( -40, 48, -110 ), 18 );
  add_sphere_helper( brown, Point3D( -10, 53, -120 ), 18 );    // 15

  add_sphere_helper( lightPurple, Point3D( -55, -52, -100 ), 10 );
  add_sphere_helper( brown, Point3D( 5, -52, -100 ), 15 );
  add_sphere_helper( darkPurple, Point3D( -20, -57, -120 ), 15 );
  add_sphere_helper( darkGreen, Point3D( 55, -27, -100 ), 17 );
  add_sphere_helper( brown, Point3D( 50, -47, -120 ), 15 );    // 20

  add_sphere_helper( lightPurple, Point3D( 70, -42, -150 ), 10 );
  add_sphere_helper( lightPurple, Point3D( 5, 73, -130 ), 12 );
  add_sphere_helper( darkPurple, Point3D( 66, 21, -130 ), 13 );
  add_sphere_helper( lightPurple, Point3D( 72, -12, -140 ), 12 );
  add_sphere_helper( green, Point3D( 64, 5, -160 ), 11 );    // 25

  add_sphere_helper( lightPurple, Point3D( 55, 38, -160 ), 12 );
  add_sphere_helper( lightPurple, Point3D( -73, -2, -160 ), 12 );
  add_sphere_helper( darkPurple, Point3D( 30, -62, -140 ), 15 );
  add_sphere_helper( darkPurple, Point3D( 25, 63, -140 ), 15 );
  add_sphere_helper( darkPurple, Point3D( -60, 46, -140 ), 15 );    // 30

  add_sphere_helper( lightPurple, Point3D( -30, 68, -130 ), 12 );
  add_sphere_helper( green, Point3D( 58, 56, -180 ), 11 );
  add_sphere_helper( green, Point3D( -63, -39, -180 ), 11 );
  add_sphere_helper( lightPurple, Point3D( 46, 68, -200 ), 10 );
  add_sphere_helper( lightPurple, Point3D( -3, -72, -130 ), 12 );    // 35
}

void World::init_plane( void ) {
  // vertical plane
  // Matte material reflection coefficients - common to all materials
  float    ka = 0.25;
  float    kd = 0.75;
  RGBColor grey( 0.50 );    // medium grey

  Matte *matte_ptr36 = new Matte;
  matte_ptr36->set_ka( ka );
  matte_ptr36->set_kd( kd );
  matte_ptr36->set_cd( grey );
  Plane *plane_ptr = new Plane( Point3D( 0, 0, -150 ), Normal( 0, 0, 1 ) );
  plane_ptr->set_material( matte_ptr36 );
  add_object( plane_ptr );
}

void World::init_light( void ) {
  // the ambient light here is the same as the default set in the World
  // constructor, and can therefore be left out
  Ambient *ambient_ptr = new Ambient;
  ambient_ptr->scale_radiance( 1.0 );
  set_ambient_light( ambient_ptr );
  background_color = black;    // default color - this can be left out
  tracer_ptr       = new RayCast( this );

  // light
  Directional *light_ptr1 = new Directional;
  //    light_ptr1->set_direction(100, 100, 200);      // spheres, city view
  //    light_ptr1->scale_radiance(3.0);

  light_ptr1->set_direction( -100, -300, 200 );    // practical view
  light_ptr1->scale_radiance( 4.0 );
  add_light( light_ptr1 );
}

void World::init_viewplane() {
  int num_samples = 25;
  vp.set_hres( 420 );
  vp.set_vres( 400 );
  vp.set_sampler( new Jittered( num_samples ) );

  vp.set_pixel_size( 0.5 );
  vp.set_samples( num_samples );
}

void World::init_cameras( Point3D eye, Point3D lookat, double view_distance, Point3D up ) {
  // camera
  Pinhole *pinhole_ptr = new Pinhole;

  pinhole_ptr->set_eye( eye );
  pinhole_ptr->set_lookat( lookat );
  pinhole_ptr->set_view_distance( view_distance );
  pinhole_ptr->set_up_vector( up );
  Vector3D up_v = pinhole_ptr->get_up_vector();
  std::cout << up_v.x << " " << up_v.y << " " << up_v.z << "\n";

  pinhole_ptr->compute_uvw();
  set_camera( pinhole_ptr );
}

void World::init_environment( Point3D eye, Point3D lookat, double view_distance, Point3D up ) {
  init_cameras( eye, lookat, view_distance, up );
  init_viewplane();
  init_light();
  init_plane();
}

void World::checkerboard_row( RGBColor color1, RGBColor color2, int y, int xmin, int xmax, int z ) {
  for ( int x = xmin; x <= xmax; x += 1 ) {
    RGBColor color = x % 2 == 0 ? color1 : color2;
    add_rect_helper( color, Point3D( x, y, z ), Vector3D( 0, 1, 0 ), Vector3D( 1, 0, 0 ), Normal( 0, 0, 1 ) );
  }
}

//void World::build_checkerboard(RGBColor c1, RGBColor c2, int cols, int z) {
void World::build_checkerboard( RGBColor c1, RGBColor c2, int xmin, int ymin, int xmax, int ymax, int z ) {
  for ( int y = ymin; y <= ymax; y += 2 ) {
    std::cout << "building checkerboard from (" << xmin << ", " << ymin << ") to (" << xmax << ", " << ymax << ")\n";
    std::flush( std::cout );
    checkerboard_row( c1, c2, y, xmin, xmax, z );

    std::cout << "NOW building checkerboard from (" << xmin << ", " << ymin << ") to (" << xmax << ", " << ymax << ")\n";
    std::flush( std::cout );
    checkerboard_row( c2, c1, y + 1, xmin, xmax, z );
  }
}

void World::build_city( void ) {
  add_bb_helper( yellow, Point3D( 1, 1, -40 ), Point3D( 2, 2, 20 ) );
  add_bb_helper( lightPurple, Point3D( 0, 0, -40 ), Point3D( 1, 1, 20 ) );
  add_bb_helper( grey, Point3D( -2, 2, -40 ), Point3D( -1, 3, 25 ) );
  add_bb_helper( darkGreen, Point3D( -4, 0, -40 ), Point3D( -3, 1, 30 ) );
  add_bb_helper( darkPurple, Point3D( 3, 0, -40 ), Point3D( 4, 1, 25 ) );

  add_bb_helper( darkBlue, Point3D( 3, -4, -40 ), Point3D( 4, -3, 30 ) );
  add_bb_helper( darkPurple, Point3D( -3, -4, -40 ), Point3D( -2, -3, 35 ) );
  add_bb_helper( yellow, Point3D( 3, 3, -40 ), Point3D( 4, 4, 30 ) );
  add_bb_helper( lightGreen, Point3D( 0, -3, -40 ), Point3D( 1, -2, 30 ) );
  add_bb_helper( darkBlue, Point3D( 0, 2, -40 ), Point3D( 1, 3, 30 ) );

  add_bb_helper( lightBlue, Point3D( -2, 0, -40 ), Point3D( -1, 1, 30 ) );
  add_bb_helper( lightBlue, Point3D( -4, -3, -40 ), Point3D( -3, -2, 40 ) );
  add_bb_helper( grey, Point3D( 2, -2, -40 ), Point3D( 3, -1, 20 ) );
  add_bb_helper( red, Point3D( -4, 3, -40 ), Point3D( -3, 4, 25 ) );

  add_bb_helper( darkBlue, Point3D( -6, -5, -40 ), Point3D( -5, -4, 40 ) );
  add_bb_helper( lightGreen, Point3D( 0, 5, -40 ), Point3D( 1, 6, 20 ) );
  add_bb_helper( darkPurple, Point3D( 3, 5, -40 ), Point3D( 4, 6, 25 ) );
  add_bb_helper( lightBlue, Point3D( 4, 1, -40 ), Point3D( 5, 2, 30 ) );
  add_bb_helper( red, Point3D( -5, -3, -40 ), Point3D( -4, -2, 35 ) );
  add_bb_helper( lightGreen, Point3D( 5, -2, -40 ), Point3D( 6, -1, 20 ) );

  add_bb_helper( darkGreen, Point3D( -2, 4, -40 ), Point3D( -1, 5, 30 ) );
  add_bb_helper( lightBlue, Point3D( -5, 2, -40 ), Point3D( -4, 3, 30 ) );
  add_bb_helper( darkBlue, Point3D( -5, 5, -40 ), Point3D( -4, 6, 20 ) );
  add_bb_helper( darkPurple, Point3D( -5, -2, -40 ), Point3D( -4, -1, 20 ) );

  add_bb_helper( darkGreen, Point3D( -2, -4, -40 ), Point3D( -1, -3, 25 ) );
  add_bb_helper( darkBlue, Point3D( -2, -2, -40 ), Point3D( -1, -1, 30 ) );
  add_bb_helper( darkBlue, Point3D( -6, -1, -40 ), Point3D( -5, 0, 30 ) );
}

#define SIDE    1
#define SPACING 3
#define COLUMNS 20
#define HEIGHT  4

void World::build_practical() {
  // init_environment(Point3D(-3.5, -3.5, 5), Point3D(2, 2, 5), 90.0, Point3D(0, 0, 1)); // a
  // init_environment(Point3D(-4, -4, 8), Point3D(2, 2, 6), 80.0, Point3D(0, 0, 1)); // b
  // init_environment(Point3D(-18.5, 5, 9), Point3D(2, 5, 9), 200.0, Point3D(0, 0, 1)); // c

  int num_x   = 20;
  int num_y   = num_x - 3;
  int spacing = 3;

  // Dark Orange Pillars X
  int height_darkOrange = 4;
  for ( int i = 0; i < num_x; i++ ) {
    add_bb_helper( darkOrange, Point3D( i * spacing, 0, 0 ), Point3D( i * spacing + 1, 1, height_darkOrange ) );
  }

  // Dark Orange Pillars Y
  for ( int i = 0; i < num_y; i++ ) {
    add_bb_helper( darkOrange, Point3D( 0, spacing * ( i + 3 ), 0 ),
                   Point3D( 1, spacing * ( i + 3 ) + 1, height_darkOrange ) );
  }

  // Green Cyan Pillars X
  int height_greenCyan = 8;
  for ( int i = 0; i < num_x; i++ ) {
    add_bb_helper( greenCyan, Point3D( i * spacing, spacing, 0 ), Point3D( i * spacing + 1, spacing + 1, height_greenCyan ) );
  }

  // Light Green Pillars X
  int height_lightGreen = 16;
  for ( int i = 0; i < num_x; i++ ) {
    add_bb_helper( lightGreen, Point3D( i * spacing, spacing * 2, 0 ),
                   Point3D( i * spacing + 1, spacing * 2 + 1, height_lightGreen ) );
  }
}

void build_box_sphere_triangle( World *w ) {
  w->add_sphere_helper( lightGreen, Point3D( -0.45, -0.4, 1.45 ), 0.5 );
  w->add_bb_helper( darkOrange, Point3D( 0.2, -0.2, 0 ), 0.7, 1.0, 2, 0 );
  w->add_triangle_helper( greenCyan, Point3D( -1.1, -0.8, 0.15 ), Point3D( 1.2, -0.2, 1.1 ), Point3D( -0.4, 0.3, 1.5 ) );

  //    add_sphere_helper(lightGreen, Point3D(-45,-40,45), 50);
  //    add_bb_helper(darkOrange, Point3D(20,-20,-100), Point3D(90,100,100));
  //    add_triangle_helper(greenCyan, Point3D(-110, -80, -85),
  //                                   Point3D( 120, -20,  10),
  //                                   Point3D(-40 ,  30,  50));
}

void World::build() {
  //  to build spheres...
  // eye,           lookat,       viewDistance,  normal=Point3D(0,0,1)
  //    init_environment(Point3D(0, 0, 500), Point3D(0.0), 600.0);        // change init_lights() too
  //    build_spheres();

  //  OR... to build the city
  // init_environment( Point3D( -0.5, 0, 70 ), Point3D( -0.5, 0, 10 ), 600.0 );
  // build_city();
  // build_checkerboard( white, lightGrey, -7, -7, 7, 7, -10 );

  //  OR... to build the practical environment
  // init_environment( Point3D( -3.5, -3.5, 5 ), Point3D( 2, 2, 5 ), 90.0, Point3D( 0, 0, 1 ) );    // a
  // init_environment( Point3D( -4, -4, 8 ), Point3D( 2, 2, 6 ), 80.0, Point3D( 0, 0, 1 ) );        // b
  // init_environment( Point3D( -18.5, 5, 9 ), Point3D( 2, 5, 9 ), 200.0, Point3D( 0, 0, 1 ) );     // c
  // build_practical();
  // build_checkerboard( white, lightGrey, -2, -2, 2, 2, 0 );      // small
  // build_checkerboard( white, lightGrey, -4, -4, 4, 4, 0 );      // fastest
  // build_checkerboard( white, lightGrey, -4, -4, 14, 14, 0 );    // fast
  // build_checkerboard( white, lightGrey, -4, -4, 26, 26, 0 );    // slower
  // build_checkerboard( white, lightGrey, -8, -8, 52, 52, 0 );    // very slow

  // init_environment( Point3D( 1, 1, 6 ), Point3D( 2, 1, -6 ), 130.0, Point3D( 0, 0, 1 ) );    // top

  init_environment( Point3D( 0, -5, 1 ), Point3D( 0, 0, 1 ), 300.0, Point3D( 0, 0, 1 ) );    // a
  // init_environment( Point3D( 3, -5, 5 ), Point3D( 0, 0, 0.5 ), 300.0, Point3D( 0, 0, 1 ) );     // b
  // init_environment( Point3D( -10, 5, 21 ), Point3D( 0, -1, 0 ), 300.0, Point3D( 0, 0, 1 ) );    // c
  build_box_sphere_triangle( this );
  // build_checkerboard( white, lightGrey, -4, -2, 4, 4, 0 );

  // init_environment( Point3D( 0, -500, 0 ), Point3D( 0, 0, 0 ), 300.0, Point3D( 0, 0, 1 ) );
  // init_environment( Point3D( 300, -500, 400 ), Point3D( 0, 0, -50 ), 250.0, Point3D( 0, 0, 1 ) );
  // init_environment( Point3D( -1000, 500, 2000 ), Point3D( 0, -100, 0 ), 250.0, Point3D( 0, 0, 1 ) );

  // add_sphere_helper( lightGreen, Point3D( -45, -40, 45 ), 50 );
  // add_bb_helper( darkOrange, Point3D( 20, -20, -100 ), Point3D( 90, 100, 100 ) );
  // add_triangle_helper( greenCyan, Point3D( -110, -80, -85 ), Point3D( 120, -20, 10 ), Point3D( -40, 30, 50 ) );
}
