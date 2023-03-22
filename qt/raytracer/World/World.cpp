// This builds a scene that consists of 35 shaded spheres and a plane.
// The objects are illuminated by a directional light and rendered with
// ambient and diffuse shading.
// Perspective viewing is used with a pinhole camera.
// Jittered sampling for antialiasing is hardwired into the PinHole::render_scene function.
// There are no sampler classes in this project.
// These are in the Chapter 5 download file.
// The spheres are the same as those in the Chapter 14 page one image.

#include "World.h"
#include "World/World_builder.h"
#include "World/Worlds.h"

#include "Cameras/Pinhole.h"

#include "GeometricObjects/Primitives/Plane.h"

#include "Lights/Directional.h"

#include "Materials/Matte.h"
#include "Materials/Phong.h"

#include "Tracers/RayCast.h"

#include "Samplers/Jittered.h"
#include "Utilities/Normal.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"

#include "Worlds.h"

// -------------------------------------------------------------------- default constructor

// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World() : background_color( black ), tracer_ptr( nullptr ), ambient_ptr( new Ambient ), camera_ptr( nullptr ) {}

//------------------------------------------------------------------ destructor
World::~World() {
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
  std::vector<int> pixels;
  std::iota( pixels.begin(), pixels.end(), vres * hres );
  for ( int el : pixels ) { qDebug( "%d ", el ); }

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
  float max_value = max( c.r, max( c.g, c.b ) );
  return ( max_value > 1.0 ? ( c / max_value ) : c );
}

// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one
RGBColor World::clamp_to_color( const RGBColor &raw_color ) const {
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
  RGBColor mapped_color;

  //    mapped_color = vp.show_out_of_gamut ? clamp_to_color(raw_color) : max_to_one(raw_color);
  if ( vp.show_out_of_gamut )
    mapped_color = clamp_to_color( raw_color );
  else
    mapped_color = max_to_one( raw_color );

  if ( vp.gamma != 1.0 ) { mapped_color = mapped_color.powc( vp.inv_gamma ); }

  int x = column;
  int y = vp.vres - row - 1;
  paintArea->setPixel( x, y, (int) ( mapped_color.r * 255 ), (int) ( mapped_color.g * 255 ), (int) ( mapped_color.b * 255 ) );
}
// ----------------------------------------------------------------------------- hit_objects
ShadeRec World::hit_objects( const Ray &ray ) {
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

ShadeRec World::hit_bare_bones_objects( const Ray &ray ) {    // ONLY in chapter 3:  bare-bones ray tracing
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
      sr.color         = objects[j]->get_color();
    }
  }
  return ( sr );
}

//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty
void World::delete_objects() {
  int num_objects = (int) objects.size();
  for ( int j = 0; j < num_objects; j++ ) {
    delete objects[j];
    objects[j] = nullptr;
  }
  objects.erase( objects.begin(), objects.end() );
}
//------------------------------------------------------------------ delete_lights
void World::delete_lights() {
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

  std::shared_ptr<Matte> ptr = std::make_shared<Matte>();

  //    std::shared_ptr<Phong> ptr = std::make_shared<Phong>();
  //    std::shared_ptr<Plastic> ptr = std::make_shared<Plastic>();
  //    std::shared_ptr<Reflective> ptr = std::make_shared<Reflective>();
  //    ptr->set_kr(1.5);

  ptr->set_ka( ka );
  ptr->set_kd( kd );
  ptr->set_cd( color );

  //    ptr->set_ks(0.25);   // Phong only
  //    ptr->set_exp(1.5);  // Phong only

  geo->set_material( ptr );
}

void World::init_plane( void ) {
  // vertical plane
  // Matte material reflection coefficients - common to all materials
  float    ka = 0.25;
  float    kd = 0.75;
  RGBColor grey( 0.25 );

  std::shared_ptr<Matte> matte_ptr36 = std::make_shared<Matte>();
  matte_ptr36->set_ka( ka );
  matte_ptr36->set_kd( kd );
  matte_ptr36->set_cd( grey );

  Plane *plane_ptr = new Plane( Point3D( 0, 0, -150 ), Normal( 0, 0, 1 ) );
  plane_ptr->set_material( matte_ptr36 );
  add_object( plane_ptr );
}

void World::init_viewplane() {
  int num_samples = 25;

  vp.set_hres( VIEWPLANE_HRES );
  vp.set_vres( VIEWPLANE_VRES );

  vp.set_sampler( new Jittered( num_samples ) );

  vp.set_pixel_size( 0.5 );
  vp.set_samples( num_samples );
}

void World::init_ambient_light( double radiance ) {
  Ambient *ambient = new Ambient;

  ambient->scale_radiance( radiance );
  set_ambient_light( ambient );
  background_color = black;
}

void World::build() {
  //  build_sphere_world( this );
  //  build_city_world( this );
  //  build_practical_world( this );

  //  build_sphere_triangle_box_world( this, A );
  //  build_olympic_rings_world( this );    // TODO:  fill in code in Worlds.cpp, , adjust lights and cameras, and run

  //  build_figure_10_10( this, A );    //  to generate 10.10a, b or c    --- thin lens

  //  build_mcdonalds_world( this );
  //  build_discussion_world( this );
  build_stonehenge_world( this );

  check();    // checks for valid camera, viewplane, lights, plane...
}
