#include "World/World.h"
#include "World_builder.h"
#include "Materials/Reflective.h"
#include "Materials/Transparent.h"

#include "Cameras/Fisheye.h"
#include "Cameras/Pinhole.h"
#include "Cameras/StereoCamera.h"
#include "Cameras/ThinLens.h"

#include "GeometricObjects/Instance.h"

#include "GeometricObjects/BeveledObjects/BeveledBox.h"

#include "GeometricObjects/CompoundObjects/Box.h"
#include "GeometricObjects/CompoundObjects/Grid.h"
#include "GeometricObjects/CompoundObjects/RoundRimmedBowl.h"
#include "GeometricObjects/CompoundObjects/SolidCylinder.h"
#include "GeometricObjects/CompoundObjects/SolidCone.h"
#include "GeometricObjects/CompoundObjects/ThickRing.h"

#include "GeometricObjects/PartObjects/ConvexPartSphere.h"

#include "GeometricObjects/Triangles/Triangle.h"

#include "GeometricObjects/Primitives/Plane.h"
#include "GeometricObjects/Primitives/Torus.h"

#include "Lights/Directional.h"
#include "Lights/PointLight.h"

#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "Materials/Reflective.h"

#include "Textures/Checker3D.h"
#include "Textures/ImageTexture.h"

#include "Samplers/MultiJittered.h"
#include "Samplers/Jittered.h"

#include "Tracers/RayCast.h"

#include "World/Worlds.h"

RGBColor lightRed( 1, 0.4, 0.4 );
RGBColor darkRed( 0.9, 0.1, 0.1 );

RGBColor brown( 0.71, 0.40, 0.16 );
RGBColor redBrown( 0.85, 0.6, 0.2 );

RGBColor orange( 1, 0.6, 0.2 );

RGBColor lemon( 1, 1, 0.33 );
RGBColor yellow( 1, 1, 0 );
RGBColor darkYellow( 0.61, 0.61, 0 );

RGBColor lightGreen( 0.65, 0.8, 0.30 );
RGBColor lightLightGreen( 0.85, 1.0, 0.6 );
RGBColor green( 0, 0.6, 0.3 );
RGBColor realGreen( 0, 1.0, 0.1 );
RGBColor darkGreen( 0.0, 0.81, 0.41 );

RGBColor cyan( 0, 1, 1 );
RGBColor blue_green( 0.1, 1, 0.5 );
RGBColor blue( 0, 1, 1 );

RGBColor lightLightBlue( 0.4, 0.64, 0.82 );
RGBColor lightBlue( 0.1, 0.4, 0.8 );
RGBColor darkBlue( 0.0, 0.0, 1.0 );

RGBColor lightPurple( 0.65, 0.3, 1 );
RGBColor darkPurple( 0.5, 0, 1 );

RGBColor lightLightGrey( 0.9 );
RGBColor lightGrey( 0.7 );
RGBColor grey( 0.25 );
RGBColor darkDarkGrey( 0.2, 0.2, 0.2 );

RGBColor darkBlack( 0, 0, 0 );

struct ColorCenterRadius {
  RGBColor color;
  Point3D  center;
  int      radius;
};

void build_spheres_helper( World *w, const std::vector<ColorCenterRadius> &spheres ) {
  for ( const ColorCenterRadius &s : spheres ) { add_sphere_helper( w, s.color, s.center, s.radius ); }
}

void build_spheres( World *w ) {
  std::vector<ColorCenterRadius> spheres = {
    {     yellow,   Point3D( 5,   3,    0 ), 30},
    {      brown,  Point3D( 45,  -7,  -60 ), 20},
    {  darkGreen,  Point3D( 40,  43, -100 ), 17},
    {     orange, Point3D( -20,  28,  -15 ), 20},
    {      green, Point3D( -25,  -7,  -35 ), 27},

    { lightGreen,  Point3D( 20, -27,  -35 ), 25},
    {      green,  Point3D( 35,  18,  -35 ), 22},
    {      brown, Point3D( -57, -17,  -50 ), 15},
    { lightGreen, Point3D( -47,  16,  -80 ), 23},
    {  darkGreen, Point3D( -15, -32,  -60 ), 22},

    { darkYellow, Point3D( -35, -37,  -80 ), 22},
    { darkYellow,  Point3D( 10,  43,  -80 ), 22},
    { darkYellow,  Point3D( 30,  -7,  -80 ), 10}, // hidden
    {  darkGreen, Point3D( -40,  48, -110 ), 18},
    {      brown, Point3D( -10,  53, -120 ), 18},

    {lightPurple, Point3D( -55, -52, -100 ), 10},
    {      brown,   Point3D( 5, -52, -100 ), 15},
    { darkPurple, Point3D( -20, -57, -120 ), 15},
    {  darkGreen,  Point3D( 55, -27, -100 ),  1},
    {      brown,  Point3D( 50, -47, -120 ), 15},

    {lightPurple,  Point3D( 70, -42, -150 ), 10},
    {lightPurple,   Point3D( 5,  73, -130 ), 12},
    { darkPurple,  Point3D( 66,  21, -130 ), 13},
    {lightPurple,  Point3D( 72, -12, -140 ), 12},
    {      green,  Point3D( 64,   5, -160 ), 11},

    {lightPurple,  Point3D( 55,  38, -160 ), 12},
    {lightPurple, Point3D( -73,  -2, -160 ), 12},
    { darkPurple,  Point3D( 30, -62, -140 ), 15},
    { darkPurple,  Point3D( 25,  63, -140 ), 15},
    { darkPurple, Point3D( -60,  46, -140 ), 15},

    {lightPurple, Point3D( -30,  68, -130 ), 12},
    {      green,  Point3D( 58,  56, -180 ), 11},
    {      green, Point3D( -63, -39, -180 ), 11},
    {lightPurple,  Point3D( 46,  68, -200 ), 10},
    {lightPurple,  Point3D( -3, -72, -130 ), 12}
  };

  build_spheres_helper( w, spheres );
}

void build_sphere_world( World *w ) {
  Pinhole *camera = new Pinhole;
  camera->set_eye( 0, 0, 500 );
  camera->set_lookat( 0.0 );
  camera->set_view_distance( 600.0 );
  // use default up vector and uvw
  w->set_camera( camera );

  w->init_viewplane();

  w->init_ambient_light();
  Directional *lt = new Directional();
  lt->set_shadows( true );
  lt->set_direction( 300, 100, 200 );
  lt->scale_radiance( 7.0 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_spheres( w );
}

struct ColorBottomTop {
  RGBColor color;
  Point3D  bottom;
  Point3D  top;
};

void build_city_helper( World *w, const std::vector<ColorBottomTop> &buildings ) {
  for ( const ColorBottomTop &bldg : buildings ) { add_bb_helper( w, bldg.color, bldg.bottom, bldg.top ); }
}
void build_city( World *w ) {
  std::vector<ColorBottomTop> buildings = {
    {    yellow,  Point3D( 1,  1, 0 ),  Point3D( 2,  2, 60 )},
    {darkPurple,  Point3D( 0,  0, 0 ),  Point3D( 1,  1, 60 )},
    {      grey, Point3D( -2,  2, 0 ), Point3D( -1,  3, 65 )},
    {     green, Point3D( -4,  0, 0 ), Point3D( -3,  1, 70 )},
    {darkPurple,  Point3D( 3,  0, 0 ),  Point3D( 4,  1, 65 )},

    {  darkBlue,  Point3D( 3, -4, 0 ),  Point3D( 4, -3, 70 )},
    {darkPurple, Point3D( -3, -4, 0 ), Point3D( -2, -3, 75 )},
    {    yellow,  Point3D( 3,  3, 0 ),  Point3D( 4,  4, 70 )},
    {     green,  Point3D( 0, -3, 0 ),  Point3D( 1, -2, 70 )},
    {  darkBlue,  Point3D( 0,  2, 0 ),  Point3D( 1,  3, 70 )},

    {  darkBlue, Point3D( -2,  0, 0 ), Point3D( -1,  1, 70 )},
    {  darkBlue, Point3D( -4, -3, 0 ), Point3D( -3, -3, 80 )},
    {      grey,  Point3D( 2, -2, 0 ),  Point3D( 3, -1, 60 )},
    {       red, Point3D( -4,  3, 0 ), Point3D( -3,  4, 65 )},

    {  darkBlue, Point3D( -6, -5, 0 ), Point3D( -5, -5, 80 )},
    {     green,  Point3D( 0,  5, 0 ),  Point3D( 1,  6, 60 )},
    {darkPurple,  Point3D( 3,  5, 0 ),  Point3D( 4,  6, 65 )},
    {  darkBlue,  Point3D( 4,  1, 0 ),  Point3D( 5,  2, 70 )},
    {  lightRed, Point3D( -5, -3, 0 ), Point3D( -4, -2, 75 )},
    {     green,  Point3D( 5, -2, 0 ),  Point3D( 6, -1, 60 )},

    {     green, Point3D( -2,  4, 0 ), Point3D( -1,  5, 70 )},
    {  darkBlue, Point3D( -5,  2, 0 ), Point3D( -4,  3, 70 )},
    {  darkBlue, Point3D( -5,  5, 0 ), Point3D( -4,  6, 60 )},
    {darkPurple, Point3D( -5, -2, 0 ), Point3D( -4, -1, 60 )},
    {     green, Point3D( -2, -4, 0 ), Point3D( -1, -3, 65 )},
    {  darkBlue, Point3D( -2, -2, 0 ), Point3D( -1, -1, 70 )},
    {  darkBlue, Point3D( -6, -1, 0 ), Point3D( -5,  0, 70 )}
  };

  build_city_helper( w, buildings );
  Plane *plane = new Plane( Point3D( -30, -30, 0 ), Normal( 0, 0, 1 ) );
  build_checkerboard( plane, grey, white, 2 );
  w->add_object( plane );
}
void build_city_world( World *w, double distance ) {
  Pinhole *camera = new Pinhole;
  camera->set_eye( -0.5, 0, 110 );
  camera->set_lookat( -0.5, 0, -10 );
  camera->set_view_distance( distance );
  camera->compute_uvw();
  w->set_camera( camera );

  w->init_viewplane();

  w->init_ambient_light();
  Directional *lt = new Directional();
  lt->set_shadows( true );
  lt->set_direction( -130, -15, 30 );
  lt->scale_radiance( 5 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_city( w );
}

#define SPACING 5
#define SIDE    1

void add_checkerboard( World *w, const RGBColor &c1, const RGBColor &c2, int size ) {
  Plane *plane = new Plane( Point3D( -30, -30, 0 ), Normal( 0, 0, 1 ) );
  build_checkerboard( plane, c1, c2, size );
  w->add_object( plane );
}

void build_practical( World *w ) {
  for ( int i = 0; i < 60; i += SPACING ) {
    add_bb_helper( w, orange, Point3D( i, 0, 0 ), SIDE, SIDE, 4 );
    add_bb_helper( w, orange, Point3D( 0, 3 * SPACING + i, 0 ), SIDE, SIDE, 4 );

    add_bb_helper( w, cyan, Point3D( i, SPACING, 0 ), SIDE, SIDE, 8 );

    add_bb_helper( w, green, Point3D( i, 2 * SPACING, 0 ), SIDE, SIDE, 16 );
  }

  add_checkerboard( w, lightGrey, white, 1 );
}
void build_practical_world( World *w, double distance ) {
  Pinhole *camera = new Pinhole;
  camera->set_eye( -6, -5, 9 );
  camera->set_lookat( -1, 0, 7 );
  camera->set_view_distance( distance );    // camera->set_view_distance(800.0);
  camera->set_up_vector( 1, 1, 1 );
  camera->compute_uvw();
  w->set_camera( camera );

  w->init_viewplane();

  w->init_ambient_light();
  Directional *lt = new Directional();
  lt->set_shadows( true );
  lt->set_direction( 10, -30, 10 );
  lt->scale_radiance( 8.5 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_practical( w );
}

void build_sphere_triangle_box( World *w ) {
  //  add_sphere_helper( w, lightGreen, Point3D( 1.7, -0.2, 1.7 ), SIDE / 2.5 );
  //  add_bb_helper( w, orange, Point3D( 2, 0, 0 ), 0.75 * SIDE, SIDE, 2.5 );
  add_sphere_helper( w, lightGreen, Point3D( -0.45, -0.4, 1.45 ), 0.5 );
  add_bb_helper( w, orange, Point3D( 0.2, -0.2, 0 ), 0.7, 1.0, 2 );

  std::shared_ptr<Phong> phong = std::make_shared<Phong>();
  phong->set_cd( cyan );
  phong->set_ka( 0.5 );
  phong->set_kd( 0.5 );
  phong->set_ks( 0.06 );
  phong->set_exp( 1 );

  //  Triangle *triangle = new Triangle( Point3D( 0.7, -1, 0.2 ), Point3D( 3, 0, 1.25 ), Point3D( 1.5, 0.5, 1.75 ) );
  Triangle *triangle = new Triangle( Point3D( -1.1, -0.8, 0.15 ), Point3D( 1.2, -0.2, 1.1 ), Point3D( -0.4, 0.3, 1.5 ) );
  triangle->set_material( phong );
  w->add_object( triangle );

  add_checkerboard( w, lightGrey, white, 1 );
}
void build_sphere_triangle_box_world( World *w, CHOICE choice ) {
  Pinhole *camera = new Pinhole;
  switch ( choice ) {
  case A:    // front
    //      camera->set_eye( 1, -4, 2 );
    //      camera->set_lookat( 0, 10, 2 );
    //      camera->set_view_distance( 150 );
    camera->set_eye( 0, -5, 1 );
    camera->set_lookat( 0, 0, 1 );
    camera->set_view_distance( 300 );
    break;
  case B:    // medium
    //    camera->set_eye( 4, -4, 6 );
    //    camera->set_lookat( -4, 4, -10 );
    //    camera->set_view_distance( 200 );
    camera->set_eye( 3, -5, 5 );
    camera->set_lookat( 0, 0, 0.5 );
    camera->set_view_distance( 300 );
    break;
  case C:    // overhead
    //    camera->set_eye( 3, -4, 15 );
    //    camera->set_lookat( 0, 0, -10 );
    //    camera->set_view_distance( 100 );
    camera->set_eye( -10, 5, 21 );
    camera->set_lookat( 0, -1, 0 );
    camera->set_view_distance( 300 );
    break;
  default: throw new std::invalid_argument( "Invalid choice\n" ); break;
  }
  camera->set_up_vector( 0, 0, 1 );
  camera->compute_uvw();
  w->set_camera( camera );

  w->init_viewplane();

  w->init_ambient_light();
  Directional *lt = new Directional();
  lt->set_shadows( true );
  lt->set_direction( 50, -50, 300 );
  lt->scale_radiance( 4.0 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_sphere_triangle_box( w );
}

void thin_lens_helper( World *w, const Point3D &p1, const Point3D &p2, const RGBColor &c1, const RGBColor &c2 ) {
  Checker3D *check = new Checker3D;
  check->set_size( 2.0 );
  check->set_color1( c1 );
  check->set_color2( c2 );

  std::shared_ptr<SV_Matte> matte = std::make_shared<SV_Matte>();
  matte->set_ka( 0.5 );
  matte->set_kd( 0.35 );
  matte->set_cd( check );

  Box *b = new Box( p1, p2 );
  b->set_material( matte );
  w->add_object( b );
}

void build_thinlens( World *w, double focal_distance ) {
  int num_samples = 100;

  w->vp.set_hres( 400 );
  w->vp.set_vres( 300 );
  w->vp.set_pixel_size( 0.05 );
  w->vp.set_sampler( new MultiJittered( num_samples ) );
  w->vp.set_max_depth( 0 );

  w->tracer_ptr       = new RayCast( w );
  w->background_color = white;

  Ambient *ambient_ptr = new Ambient;
  ambient_ptr->scale_radiance( 0.5 );
  w->set_ambient_light( ambient_ptr );

  ThinLens *tl = new ThinLens;
  tl->set_sampler( new MultiJittered( num_samples ) );
  tl->set_eye( 0, 6, 50 );
  tl->set_lookat( 0, 6, 0 );
  tl->set_view_distance( 40.0 );

  tl->set_focal_distance( focal_distance );

  tl->set_lens_radius( 1.0 );
  tl->compute_uvw();
  w->set_camera( tl );

  Directional *lp = new Directional;
  lp->set_direction( 1, 1, 1 );
  lp->scale_radiance( 7.5 );
  lp->set_shadows( true );
  w->add_light( lp );

  thin_lens_helper( w, Point3D( -9, 0, -1 ), Point3D( -3, 12, 0 ), lemon, black );
  thin_lens_helper( w, Point3D( -3.25, 0, -25 ), Point3D( 4.75, 14, -24 ), blue_green, black );
  thin_lens_helper( w, Point3D( 8, 0, -49 ), Point3D( 18, 15, -48 ), orange, black );

  Instance *isplane = new Instance( new Plane( Point3D( 0, 0, 0 ), Normal( 0, 1, 0 ) ) );
  isplane->rotate_y( 90 );
  build_checkerboard( isplane, lightGrey, black, 8 );

  w->add_object( isplane );
}

void build_figure_10_10( World *w, CHOICE choice ) {
  switch ( choice ) {
  case A: build_thinlens( w, 50.0 ); break;
  case B: build_thinlens( w, 74.0 ); break;
  case C: build_thinlens( w, 98.0 ); break;
  default: throw new std::invalid_argument( "Invalid choice.\n" );
  }
}

struct RingDims {
  RingDims( double bottom_, double top_, double inner_, double outer_ ) :
      bottom( bottom_ ), top( top_ ), inner( inner_ ), outer( outer_ ) {}
  double bottom, top;
  double inner, outer;
};

void build_cone_helper( World *w, const Point3D &posn, const RGBColor &color, double h, double r ) {
  Instance *iscone = new Instance( new SolidCone( h, r ) );
  iscone->rotate_y( 0 );
  iscone->rotate_z( 0 );
  iscone->rotate_x( 90 );
  iscone->translate( posn );

  std::shared_ptr<Phong> phong = std::make_shared<Phong>();
  phong->set_ka( 0.75 );
  phong->set_kd( 1.25 );
  phong->set_cd( color );
  phong->set_ks( 0.25 );
  phong->set_exp( 1.5 );

  iscone->set_material( phong );
  //    w->set_material(iscone, color);
  w->add_object( iscone );
}

void build_cylinder_helper( World *w, const Point3D &posn, const RGBColor &color, double b, double t, double r ) {
  Instance *iscylinder = new Instance( new SolidCylinder( b, t, r ) );
  iscylinder->rotate_y( 0 );
  iscylinder->rotate_z( 0 );
  iscylinder->rotate_x( 90 );
  iscylinder->translate( posn );
  //    iscylinder->set_material(m_ptr);

  std::shared_ptr<Phong> phong = std::make_shared<Phong>();
  phong->set_ka( 0.25 );
  phong->set_kd( 0.75 );
  phong->set_cd( green );
  phong->set_ks( 0.25 );
  phong->set_exp( 1.5 );

  w->set_material( iscylinder, color );
  w->add_object( iscylinder );
}

void build_ring_helper( World *w, const Point3D &posn, const RGBColor &color, const RingDims &rd, int r,
                        std::shared_ptr<Material> m_ptr ) {
  Instance *isring = new Instance( new ThickRing( rd.bottom, rd.top, rd.inner, rd.outer ) );
  isring->rotate_y( 0 );
  isring->rotate_z( r );
  isring->translate( posn );
  isring->set_material( m_ptr );
  w->set_material( isring, color );
  w->add_object( isring );
}

void build_axis( World *w, double length, double width ) {
  add_bb_helper( w, red, Point3D( 0, 0, 0 ), length, width, width );
  add_triangle_helper( w, red, Point3D( length, 0, 1.2 * width ), Point3D( length, 0, -0.6 * width ),
                       Point3D( length + 1.2 * width, 0, 0.6 * width ) );

  add_bb_helper( w, darkBlue, Point3D( 0, 0, 0 ), width, length, width );
  add_triangle_helper( w, darkBlue, Point3D( 0, length, 1.2 * width ), Point3D( 0, length, -0.6 * width ),
                       Point3D( 0, length + 1.2 * width, 0.6 * width ) );
}

Instance *add_torus_helper( World *w, const RGBColor &color, double a, double b, Point3D &location, Point3D scale ) {
  Instance *istorus = new Instance( new Torus( a, b ) );
  w->set_material( istorus, color );
  istorus->rotate_x( 90 );
  istorus->rotate_y( 65 );
  istorus->scale( scale );
  istorus->translate( location );
  return istorus;
}

void build_mcdonalds( World *w ) {
  //    //camera
  //    Pinhole* ptr = new Pinhole;
  //    ptr->set_eye(-2, -12, 14);        // overhead
  //    ptr->set_lookat(0, 10, -10);     // overhead
  //    ptr->set_view_distance(200);    // overhead
  //    ptr->set_up_vector(0, 0, 1);
  //    ptr->compute_uvw();
  //    w->set_camera(ptr);

  //    //viewplane
  //    int num_samples = 25;
  //    w->vp.set_hres(VIEWPLANE_HRES);
  //    w->vp.set_vres(VIEWPLANE_VRES);
  //    w->vp.set_sampler(new Jittered(num_samples));
  //    w->vp.set_pixel_size(0.5);
  //    w->vp.set_samples(num_samples);

  //    //lights
  //    Ambient* ambient_ptr = new Ambient;
  //    ambient_ptr->scale_radiance(0.2);
  //    w->set_ambient_light(ambient_ptr);
  //    w->background_color =  black;//RGBColor(0.9, 0.9, 0.9);
  //    w->tracer_ptr = new RayCast(w);

  //    Directional* lt = new Directional();
  //    lt->set_shadows(true);
  //    lt->set_direction(-30, 7, 10);
  //    lt->scale_radiance(8.5);
  //    w->add_light(lt);

  //plane
  float    ka = 0.25;
  float    kd = 0.75;
  RGBColor grey( 0.25 );

  std::shared_ptr<Phong> phong_ptr36 = std::make_shared<Phong>();
  phong_ptr36->set_ka( ka );
  phong_ptr36->set_kd( kd );
  phong_ptr36->set_cd( grey );
  phong_ptr36->set_ks( 0.25 );
  phong_ptr36->set_exp( 1.5 );

  Plane *plane_ptr = new Plane( Point3D( 0, 0, -150 ), Normal( 0, 0, 1 ) );
  plane_ptr->set_material( phong_ptr36 );
  w->add_object( plane_ptr );

  //build
  std::shared_ptr<Reflective> reflect1 = std::make_shared<Reflective>();
  reflect1->set_kr( 2.5 );
  reflect1->set_ka( 1.25 );
  reflect1->set_kd( 1.75 );
  reflect1->set_cd( lightBlue );

  Sphere *sphere2 = new Sphere( Point3D( 2.5, 0.8, 4 ), 2.5 );
  sphere2->set_material( reflect1 );
  w->add_object( sphere2 );

  RingDims rd = RingDims( 1, 2, 6.5, 8 );
  build_ring_helper( w, Point3D( -2, 0, -0.5 ), yellow, rd, 50, phong_ptr36 );
  build_ring_helper( w, Point3D( -12, 6, 1 ), yellow, rd, 45, phong_ptr36 );
  add_bb_helper( w, orange, Point3D( 0, 6, 0 ), Point3D( 3, 7, 6 ) );
  build_cone_helper( w, Point3D( -2, 3.5, 0 ), cyan, 4.0, 1.5 );
  build_cone_helper( w, Point3D( 2, -2.5, 0 ), darkBlue, 5.0, 1.5 );
  build_cylinder_helper( w, Point3D( -2.5, -1, 0 ), green, 0.0, 3.0, 1.0 );
  add_triangle_helper( w, red, Point3D( -2.8, 2.5, 2.5 ), Point3D( -2.5, -7.5, 0.5 ), Point3D( -0.5, -3, 1.5 ) );

  add_checkerboard( w, red, white, 1 );
}

void build_mcdonalds_world( World *w ) {
  //camera
  Pinhole *ptr = new Pinhole;
  ptr->set_eye( -2, -12, 14 );      // overhead
  ptr->set_lookat( 0, 10, -10 );    // overhead
  ptr->set_view_distance( 200 );    // overhead
  ptr->set_up_vector( 0, 0, 1 );
  ptr->compute_uvw();
  w->set_camera( ptr );

  //viewplane
  int num_samples = 25;
  w->vp.set_hres( VIEWPLANE_HRES );
  w->vp.set_vres( VIEWPLANE_VRES );
  w->vp.set_sampler( new Jittered( num_samples ) );
  w->vp.set_pixel_size( 0.5 );
  w->vp.set_samples( num_samples );

  //lights
  Ambient *ambient_ptr = new Ambient;
  ambient_ptr->scale_radiance( 0.2 );
  w->set_ambient_light( ambient_ptr );
  w->background_color = black;    //RGBColor(0.9, 0.9, 0.9);
  w->tracer_ptr       = new RayCast( w );

  Directional *lt = new Directional();
  lt->set_shadows( true );
  lt->set_direction( -30, 7, 10 );
  lt->scale_radiance( 8.5 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_mcdonalds( w );
}

void build_discussion( World *w ) {
  //plane
  float    ka = 0.25;
  float    kd = 0.75;
  RGBColor grey( 0.25 );

  std::shared_ptr<Phong> phong_ptr36 = std::make_shared<Phong>();
  phong_ptr36->set_ka( ka );
  phong_ptr36->set_kd( kd );
  phong_ptr36->set_cd( grey );
  phong_ptr36->set_ks( 0.25 );
  phong_ptr36->set_exp( 1.5 );

  //build
  std::shared_ptr<Reflective> reflect1 = std::make_shared<Reflective>();
  reflect1->set_kr( 2.5 );
  reflect1->set_ka( 1.25 );
  reflect1->set_kd( 1.75 );
  reflect1->set_cd( black );

  Sphere *sphere2 = new Sphere( Point3D( -4, 0, 15 ), 5 );
  sphere2->set_material( reflect1 );
  w->add_object( sphere2 );

  RingDims rd = RingDims( 0, 1, 6.5, 8 );
  build_ring_helper( w, Point3D( 0, -8, 2.5 ), blue, rd, 70, phong_ptr36 );
  build_ring_helper( w, Point3D( 0, 0, 0.5 ), blue, rd, 90, phong_ptr36 );
  build_ring_helper( w, Point3D( 0, 8, 2.5 ), blue, rd, 110, phong_ptr36 );

  for ( int i = 0; i < 5; i++ ) { add_bb_helper( w, orange, Point3D( -4, -6 + ( i * 3 ) - 0.5, 0 ), 1, 1, 6 ); }

  build_cone_helper( w, Point3D( -6, -2.5, 0 ), darkBlue, 4.0, 1.5 );
  build_cone_helper( w, Point3D( -6, 2.5, 0 ), darkBlue, 4.0, 1.5 );

  //  build_cone_helper( w, Point3D( 2, -2.5, 0 ), darkBlue, 5.0, 1.5 );
  //  build_cylinder_helper( w, Point3D( -2.5, -1, 0 ), green, 0.0, 3.0, 1.0 );
  //  add_triangle_helper( w, red, Point3D( -2.8, 2.5, 2.5 ), Point3D( -2.5, -7.5, 0.5 ), Point3D( -0.5, -3, 1.5 ) );

  add_checkerboard( w, cyan, orange, 1 );
}

void build_discussion_world( World *w ) {
  //camera
  Pinhole *ptr = new Pinhole;
  ptr->set_eye( -20, 0, 5 );
  ptr->set_lookat( 0, 0, 5 );
  ptr->set_view_distance( 200 );
  ptr->set_up_vector( 0, 0, 1 );
  ptr->compute_uvw();
  w->set_camera( ptr );

  //viewplane
  int num_samples = 25;
  w->vp.set_hres( VIEWPLANE_HRES );
  w->vp.set_vres( VIEWPLANE_VRES );
  w->vp.set_sampler( new Jittered( num_samples ) );
  w->vp.set_pixel_size( 0.5 );
  w->vp.set_samples( num_samples );

  //lights
  Ambient *ambient_ptr = new Ambient;
  ambient_ptr->scale_radiance( 0.2 );
  w->set_ambient_light( ambient_ptr );
  w->background_color = black;    //RGBColor(0.9, 0.9, 0.9);
  w->tracer_ptr       = new RayCast( w );

  Directional *lt = new Directional();
  lt->set_shadows( true );
  lt->set_direction( -30, 7, 10 );
  lt->scale_radiance( 8.5 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_discussion( w );
}
