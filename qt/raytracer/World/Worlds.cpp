#include "World/Worlds.h"
#include "Cameras/Fisheye.h"
#include <QtMath>

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

RGBColor lightLightBlue( 0.4, 0.64, 0.82 );
RGBColor lightBlue( 0.1, 0.4, 0.8 );
RGBColor darkBlue( 0.0, 0.0, 1.0 );

RGBColor lightPurple( 0.65, 0.3, 1 );
RGBColor darkPurple( 0.5, 0, 1 );

RGBColor lightLightGrey( 0.9 );
RGBColor lightGrey( 0.7 );
RGBColor darkGrey( 0.3 );
RGBColor darkBlueGrey( 0.3, 0.3, 0.5 );
RGBColor grey( 0.25 );
RGBColor darkDarkGrey( 0.2, 0.2, 0.2 );

RGBColor darkBrown( 0.18, 0.15, 0.14 );
RGBColor mediumBrown( 0.4, 0.302, 0.243 );
RGBColor darkBlack( 0, 0, 0 );

#define SPACING 3
#define SIDE    1
#define HEIGHT  6

#define ROCKS  8
#define RADIUS 32

struct ColorCenterRadius {
  RGBColor color;
  Point3D  center;
  double   radius;
};

void showpoint( const std::string &msg, Point3D pt ) { qDebug() << "(" << pt.x << "," << pt.y << "," << pt.z << ")"; }

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

  //    w->init_ambient_light();
  //    Directional* lt = new Directional();
  ////    lt->set_shadows(true);
  //    lt->set_shadows(false);
  //    lt->set_direction(300, 100, 200);
  //    lt->scale_radiance(7.0);
  //    w->add_light(lt);

  w->init_ambient_light();    // from practical world
  Directional *lt = new Directional();
  //    lt->set_shadows(true);
  lt->set_shadows( false );
  lt->set_direction( 10, -30, 10 );
  lt->scale_radiance( 8.5 );
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

void build_cylinder_helper( World *w, const Point3D &posn, const RGBColor &color, double b, double t, double r,
                            Vector3D rotation ) {
  double    delta      = t - b;
  Instance *iscylinder = new Instance( new SolidCylinder( 0, delta, r ) );

  iscylinder->rotate_y( rotation.y );
  iscylinder->rotate_z( rotation.z );
  iscylinder->rotate_x( rotation.x );

  iscylinder->translate( Point3D( posn.x, posn.y, posn.z ) );

  std::shared_ptr<Phong> phong = std::make_shared<Phong>();
  phong->set_ka( 0.3 );
  phong->set_kd( 1 );
  phong->set_cd( 0.7 );
  phong->set_ks( 0.3 );
  phong->set_exp( 50 );

  w->set_material( iscylinder, color );
  w->add_object( iscylinder );
}

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

Disk *build_disk_helper( World *w, const RGBColor &color, Point3D center, Normal normal, double radius ) {
  Disk *disk = new Disk( center, normal, radius );
  w->set_material( disk, color );
  w->add_object( disk );
  return disk;
}

void build_wireframe_helper( World *w, Point3D p0, Point3D p1, RGBColor color, double r ) {
  double b = p0.z;
  double t = p1.z;

  build_cylinder_helper( w, Point3D( p0.x, p0.y, p0.z ), color, b, t, r, Vector3D( 0, 0, -90 ) );
  build_cylinder_helper( w, Point3D( p0.x, p0.y, p0.z ), color, b, t, r, Vector3D( 0, 90, 0 ) );
  build_cylinder_helper( w, Point3D( p0.x, p0.y, p0.z ), color, b, t, r, Vector3D( 90, 0, 0 ) );

  build_cylinder_helper( w, Point3D( p1.x, p0.y, p1.z ), color, b, t, r, Vector3D( 0, 0, 90 ) );
  build_cylinder_helper( w, Point3D( p1.x, p0.y, p1.z ), color, b, t, r, Vector3D( 0, -90, 0 ) );
  build_cylinder_helper( w, Point3D( p1.x, p0.y, p1.z ), color, b, t, r, Vector3D( -90, 0, 0 ) );

  build_cylinder_helper( w, Point3D( p0.x, p1.y, p1.z ), color, b, t, r, Vector3D( 0, 0, -90 ) );
  build_cylinder_helper( w, Point3D( p0.x, p1.y, p1.z ), color, b, t, r, Vector3D( 180, 90, 0 ) );
  build_cylinder_helper( w, Point3D( p0.x, p1.y, p1.z ), color, b, t, r, Vector3D( -90, 0, 0 ) );

  build_cylinder_helper( w, Point3D( p1.x, p1.y, p0.z ), color, b, t, r, Vector3D( 0, 0, 90 ) );
  build_cylinder_helper( w, Point3D( p1.x, p1.y, p0.z ), color, b, t, r, Vector3D( 90, 90, 0 ) );
  build_cylinder_helper( w, Point3D( p1.x, p1.y, p0.z ), color, b, t, r, Vector3D( -180, 0, 0 ) );

  std::vector<ColorCenterRadius> vertices = {
    {color, Point3D( p0.x, p0.y, p1.z ), r},
    {color, Point3D( p1.x, p0.y, p1.z ), r},
    {color, Point3D( p0.x, p1.y, p1.z ), r},
    {color, Point3D( p1.x, p1.y, p1.z ), r},

    {color, Point3D( p0.x, p0.y, p0.z ), r},
    {color, Point3D( p1.x, p0.y, p0.z ), r},
    {color, Point3D( p0.x, p1.y, p0.z ), r},
    {color, Point3D( p1.x, p1.y, p0.z ), r},
  };
  build_spheres_helper( w, vertices );

  build_cone_helper( w, Point3D( 0 ), green, 1, 0.2 );
  build_disk_helper( w, red, Point3D( 0 ), Normal( 0, 0, -1 ), 0.3 );

  //    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
  //    build_checkerboard(plane, grey, white, 2);
  //    w->add_object(plane);
}

void build_city_helper( World *w, const std::vector<ColorBottomTop> &buildings ) {
  for ( const ColorBottomTop &bldg : buildings ) { add_bb_helper( w, bldg.color, bldg.bottom, bldg.top, Vector3D() ); }
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
  //    camera->set_up_vector(Vector3D(0, 0, 1));
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

void add_checkerboard( World *w, const RGBColor &c1, const RGBColor &c2, int size ) {
  Plane *plane = new Plane( Point3D( -30, -30, 0 ), Normal( 0, 0, 1 ) );
  build_checkerboard( plane, c1, c2, size );
  w->add_object( plane );
}

void build_practical( World *w ) {
  for ( int i = 0; i < 60; i += SPACING ) {
    add_bb_helper( w, orange, Point3D( i, 0, 0 ), SIDE, SIDE, HEIGHT, Vector3D() );
    add_bb_helper( w, orange, Point3D( 0, 3 * SPACING + i, 0 ), SIDE, SIDE, HEIGHT, Vector3D() );

    add_bb_helper( w, cyan, Point3D( i, SPACING, 0 ), SIDE, SIDE, 2 * HEIGHT, Vector3D() );

    add_bb_helper( w, green, Point3D( i, 2 * SPACING, 0 ), SIDE, SIDE, 4 * HEIGHT, Vector3D() );
  }

  int num_samples = 1;

  AmbientOccluder *ambient_occluder = new AmbientOccluder;
  ambient_occluder->set_sampler( new MultiJittered( num_samples ) );
  ambient_occluder->set_min_amount( 0.5 );
  w->set_ambient_light( ambient_occluder );

  Image *image = new Image;
  image->read_ppm_file( "C:/dev/school/CPSC_484-Computer-Graphics/qt/raytracer/TextureFiles/ppm/CloudsHighResWithBlack.ppm" );

  SphericalMap *spherical_map = new SphericalMap;

  ImageTexture *image_texture = new ImageTexture( image );
  image_texture->set_mapping( spherical_map );

  std::shared_ptr<SV_Matte> sv_matte = std::make_shared<SV_Matte>();
  sv_matte->set_ka( 1.0 );
  sv_matte->set_kd( 0.85 );
  //    sv_matte->set_cd(RGBColor(1, 0, 0));
  sv_matte->set_cd( image_texture );

  Instance *sphere = new Instance( new Sphere() );
  sphere->scale( 1000000 );
  sphere->set_material( sv_matte );
  sphere->set_shadows( false );    // reguired for ambient occlusion to work
  sphere->rotate_x( 90 );
  w->add_object( sphere );

  add_checkerboard( w, grey, lightGrey, 2 );
}
void build_practical_world( World *w, double distance ) {
  //    Pinhole* camera = new Pinhole;
  Fisheye *camera = new Fisheye;
  camera->set_fov( distance );
  camera->set_rectangular( true );

  //    camera->set_eye(-6, -5, 2 * HEIGHT);
  camera->set_eye( -6, -6, 1.5 * HEIGHT );
  camera->set_lookat( 0, 0, HEIGHT );
  //    camera->set_lookat(-1, 0, 7);
  //    camera->set_view_distance(distance);    // camera->set_view_distance(800.0);
  camera->set_up_vector( 1, 1, 1 );
  camera->compute_uvw();
  w->set_camera( camera );

  w->init_viewplane();

  w->init_ambient_light();
  Directional *lt = new Directional();
  lt->set_shadows( true );
  //    lt->set_shadows(false);
  lt->set_direction( 10, -30, 10 );
  lt->scale_radiance( 8.5 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_practical( w );
}

void build_sphere_triangle_box( World *w ) {
  add_sphere_helper( w, lightGreen, Point3D( 1.7, -0.2, 1.7 ), SIDE / 2.5 );
  add_bb_helper( w, orange, Point3D( 2, 0, 0 ), 0.75 * SIDE, SIDE, 2.5, Vector3D() );

  std::shared_ptr<Phong> phong = std::make_shared<Phong>();
  phong->set_cd( cyan );
  phong->set_ka( 0.5 );
  phong->set_kd( 0.5 );
  phong->set_ks( 0.06 );
  phong->set_exp( 1 );

  Triangle *triangle = new Triangle( Point3D( 0.7, -1, 0.2 ), Point3D( 3, 0, 1.25 ), Point3D( 1.5, 0.5, 1.75 ) );
  triangle->set_material( phong );
  w->add_object( triangle );

  add_checkerboard( w, lightGrey, white, 1 );
}
void build_sphere_triangle_box_world( World *w, CHOICE choice ) {
  Pinhole *camera = new Pinhole;
  switch ( choice ) {
  case A:    // front
    camera->set_eye( 1, -4, 2 );
    camera->set_lookat( 0, 10, 2 );
    camera->set_view_distance( 150 );
    break;
  case B:    // medium
    camera->set_eye( 4, -4, 6 );
    camera->set_lookat( -4, 4, -10 );
    camera->set_view_distance( 200 );
    break;
  case C:                            // overhead
    camera->set_eye( 3, -4, 15 );    // overhead
    camera->set_lookat( 0, 0, -10 );
    camera->set_view_distance( 100 );
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

void build_ring_helper( World *w, const Point3D &posn, const RGBColor &color, const RingDims &rd, double rot_x, double rot_y,
                        double rot_z, std::shared_ptr<Material> m_ptr ) {
  Instance *isring = new Instance( new ThickRing( rd.bottom, rd.top, rd.inner, rd.outer ) );
  isring->rotate_x( rot_x );
  isring->rotate_x( rot_y );
  isring->rotate_z( rot_z );
  isring->translate( posn );
  isring->set_material( m_ptr );
  w->set_material( isring, color );
  w->add_object( isring );
}

void build_axis( World *w, double length, double width ) {
  add_bb_helper( w, red, Point3D( 0, 0, 0 ), length, width, width, Vector3D() );
  add_triangle_helper( w, red, Point3D( length, 0, 1.2 * width ), Point3D( length, 0, -0.6 * width ),
                       Point3D( length + 1.2 * width, 0, 0.6 * width ) );

  add_bb_helper( w, darkBlue, Point3D( 0, 0, 0 ), width, length, width, Vector3D() );
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

Instance *build_partannulus_helper( World *w, const RGBColor &color, double i_r, double o_r, double azimuth_min,
                                    double azimuth_max, Point3D location, Point3D scale, Vector3D rotation,
                                    std::shared_ptr<Material> m_ptr, bool up = true ) {
  Instance *is_part_annulus = new Instance( new PartAnnulus( location.y, i_r, o_r, azimuth_min, azimuth_max, up ) );
  w->set_material( is_part_annulus, color );

  is_part_annulus->rotate_x( rotation.x );
  is_part_annulus->rotate_y( rotation.x );
  is_part_annulus->rotate_z( rotation.z );

  is_part_annulus->scale( scale );

  is_part_annulus->translate( location );

  w->set_material( is_part_annulus, color );
  w->add_object( is_part_annulus );
  return is_part_annulus;
}

void build_mcdonalds( World *w ) {
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
  build_ring_helper( w, Point3D( -2, 0, -0.5 ), yellow, rd, 0, 0, 50, phong_ptr36 );
  build_ring_helper( w, Point3D( -12, 6, 1 ), yellow, rd, 0, 0, 45, phong_ptr36 );

  add_bb_helper( w, orange, Point3D( 0, 6, 0 ), Point3D( 3, 7, 6 ), Vector3D() );
  build_cone_helper( w, Point3D( -2, 3.5, 0 ), cyan, 4.0, 1.5 );
  build_cone_helper( w, Point3D( 2, -2.5, 0 ), darkBlue, 5.0, 1.5 );
  build_cylinder_helper( w, Point3D( -2.5, -1, 0 ), green, 0.0, 3.0, 1.0, Vector3D( 90, 0, 0 ) );
  add_triangle_helper( w, red, Point3D( -2.8, 2.5, 2.5 ), Point3D( -2.5, -7.5, 0.5 ), Point3D( -0.5, -3, 1.5 ) );

  add_checkerboard( w, white, darkBlue, 3 );
}

void build_mcdonalds_world( World *w ) {
  //camera
  Pinhole *ptr = new Pinhole;
  ptr->set_eye( -2, -12, 14 );      // overhead
                                    //    ptr->set_eye(-2, -30, 14);        // overhead
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

void add_bb_facing_center_at_offset_rotation( World *w, const RGBColor &color, double radius, double theta, double z,
                                              double dx, double dy, double dz, double rotation_y, double offset_rotation ) {
  double x             = radius * cos( qDegreesToRadians( theta ) );
  double y             = radius * sin( qDegreesToRadians( theta ) );
  double perpendicular = theta + 90;
  add_bb_helper( w, color, Point3D( x, y, z ), dx, dy, dz, Vector3D( 0, rotation_y, perpendicular - offset_rotation ) );
  //    qDebug() << "in add_bb_facing_center_at(), theta is: " << theta;
}

void add_bb_facing_center_at( World *w, const RGBColor &color, double radius, double theta, double z, double dx, double dy,
                              double dz, double rotation_y ) {
  double x             = radius * cos( qDegreesToRadians( theta ) );
  double y             = radius * sin( qDegreesToRadians( theta ) );
  double perpendicular = theta + 90;
  add_bb_helper( w, color, Point3D( x, y, z ), dx, dy, dz, Vector3D( 0, rotation_y, perpendicular ) );
}

double add_double_bb_facing_center_at( World *w, const RGBColor &color, double radius, double theta, double dtheta, double dx,
                                       double dy, double dz ) {
  add_bb_facing_center_at( w, color, radius, theta, 4, dx, dy, dz, 0 );
  //    add_bb_facing_center_at(w, darkBlue, radius, theta + dtheta, 4, dx, dy, dz, 0);
  //    qDebug() << "in triple, dx: " << dx << ", dy: " << dy << "dz: " << dz;
  add_bb_facing_center_at( w, mediumBrown, radius, theta + dtheta / 2, 8 / 9.0 * dz, dy, dy, 8 * dz / 9.0, 90 );
  return theta;
}

double add_triple_bb_facing_center_at( World *w, const RGBColor &color, double radius, double theta, double dtheta, double dx,
                                       double dy, double dz ) {
  add_bb_facing_center_at( w, color, radius, theta, 4, dx, dy, dz, 0 );
  add_bb_facing_center_at( w, color, radius, theta + dtheta, 4, dx, dy, dz, 0 );
  //    qDebug() << "in triple, dx: " << dx << ", dy: " << dy << "dz: " << dz;
  add_bb_facing_center_at( w, mediumBrown, radius, theta + dtheta / 2, 4 / 5.0 * dz, dy, dy, 5 * dz / 9.0, 90 );
  return theta + dtheta;
}

void build_stonehenge( World *w ) {
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

  //    build_partannulus_helper(w, red, 4, 5,
  //                               0, 180, Point3D(-2, -2, 10), Point3D(1, 1, 1), Vector3D(0, 45, 180), phong_ptr36);

  //    build_cone_helper(w, Point3D(0, 0,0), green, 0.2, 0.1);

  double height      = 16;
  double radius      = 29.9;
  double theta       = 0;
  double delta_theta = 45;
  double x           = 1.3;
  double y           = 1;

  while ( theta < 300 ) {
    double x = RADIUS * cos( qDegreesToRadians( theta ) );
    double y = RADIUS * sin( qDegreesToRadians( theta ) );
    x        = abs( x ) < 0.001 ? 0 : x;
    y        = abs( y ) < 0.001 ? 0 : y;
    add_bb_facing_center_at( w, orange, RADIUS, theta, 0, 4, 2, 12, 0 );
    theta += delta_theta;
  }

  while ( theta < 210 ) {
    double x = RADIUS * cos( qDegreesToRadians( theta ) );
    double y = RADIUS * sin( qDegreesToRadians( theta ) );
    x        = abs( x ) < 0.001 ? 0 : x;
    y        = abs( y ) < 0.001 ? 0 : y;
    add_bb_facing_center_at( w, orange, RADIUS, theta, 0, 4, 2, 6, 0 );
    theta += delta_theta;
  }

  while ( theta < 600 ) {
    add_bb_facing_center_at( w, darkBrown, 0.75 * radius, theta, 4, x, y, 3 / 15.0 * height, 0 );

    theta  = add_double_bb_facing_center_at( w, darkBrown, radius, theta, delta_theta, 4.2, 1.2, 0.7 * height );
    theta += delta_theta;
  }

  theta       = 75;
  delta_theta = 20;
  while ( theta < 300 ) {
    theta  = add_triple_bb_facing_center_at( w, darkBrown, 0.5 * radius, theta, delta_theta, 3.5, 1.2, height );
    theta += 1.5 * delta_theta;
  }

  theta       = 80;
  delta_theta = 8 * 15 / 5.0;
  while ( theta < 300 ) {
    add_bb_facing_center_at( w, darkBrown, 0.3 * radius, theta, 4, x, y, 3 / 15.0 * height, 0 );
    theta += delta_theta;
  }

  x     = 4;
  y     = 2;
  theta = 195;
  add_bb_facing_center_at_offset_rotation( w, darkBrown, 0.1 * radius, theta, 4, x, y, 7 / 15.0 * height, 0, 60 );

  add_checkerboard( w, darkGreen, lightGreen, 4 );
}

void set_camera( World *w, Pinhole *pc, Point3D eye, Point3D lookat, double view_distance, Vector3D up ) {
  pc->set_eye( eye );          // overhead
  pc->set_lookat( lookat );    // overhead

  pc->set_view_distance( view_distance );    // overhead
  pc->set_up_vector( up );
  pc->compute_uvw();
  w->set_camera( pc );
}

void build_stonehenge_world( World *w ) {
  //camera
  Pinhole *ptr = new Pinhole;
  //    set_camera(w, ptr, Point3D(-22, -20, 24), Point3D(0, 1, -10), 150, Vector3D(0, 0, 1));
  //    set_camera(w, ptr, Point3D(-20, -20, 8), Point3D(0, 1, -10), 200, Vector3D(0, 0, 1));
  //    set_camera(w, ptr, Point3D(-25, -25, 1), Point3D(0, 1, 6), 200, Vector3D(0, 0, 1));
  set_camera( w, ptr, Point3D( 8, 40, 34 ), Point3D( 1, 1, -2 ), 200, Vector3D( 0, 0, 1 ) );
  //    set_camera(w, ptr, Point3D(8, 40, 64), Point3D(0, 10, -10), 200, Vector3D(0, 0, 1));

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
  //    lt->set_direction(100, 100, 16);
  lt->set_direction( 10, 10, 36 );
  //    lt->scale_radiance(12.5);
  lt->scale_radiance( 6.5 );
  w->add_light( lt );

  w->tracer_ptr = new RayCast( w );

  w->init_plane();

  build_stonehenge( w );
}

void build_stereo( World *w, int figure, CHOICE choice ) {
  int num_samples;

  w->vp.set_hres( 200 );
  w->vp.set_vres( 200 );

  w->tracer_ptr = new RayCast( w );
  float vpd;
  float fov = 200;

  Pinhole *left_camera  = new Pinhole;
  Pinhole *right_camera = new Pinhole;

  Fisheye *left_fisheye  = nullptr;
  Fisheye *right_fisheye = nullptr;

  StereoCamera *stereo = new StereoCamera;

  if ( figure == 12 ) {
    w->vp.num_samples = 1;
    vpd               = 100;    // view plane distance for 200 x 200 pixel images
    left_camera->set_view_distance( vpd );
    right_camera->set_view_distance( vpd );
    w->vp.set_pixel_size( 0.05 );
  } else if ( figure == 13 ) {
    w->vp.num_samples = 16;
    vpd               = 10;    // view plane distance for 200 x 200 pixel images
    left_camera->set_view_distance( vpd );
    right_camera->set_view_distance( vpd );
    w->vp.set_pixel_size( 0.0325 );
  } else if ( figure == 14 ) {
    w->vp.num_samples   = 16;
    w->background_color = black;
    vpd                 = 10;    // view plane distance for 200 x 200 pixel images
    left_camera->set_view_distance( vpd );
    right_camera->set_view_distance( vpd );
    w->vp.set_pixel_size( 0.05 );
  } else if ( figure == 16 ) {
    w->vp.num_samples = 16;
    w->vp.set_samples( 16 );
    w->vp.set_pixel_size( 1 );
    w->background_color = RGBColor( 0.0, 0.2, 0.4 );
    fov                 = 200;
    left_fisheye        = new Fisheye;
    right_fisheye       = new Fisheye;
    left_fisheye->set_fov( fov );
    right_fisheye->set_fov( fov );
    //        left_fisheye->set_up_vector(Vector3D(1, 0, 0));
    //        right_fisheye->set_up_vector(Vector3D(1, 0, 0));
  }

  if ( choice == A ) {
    if ( figure != 16 ) {
      stereo->set_left_camera( left_camera );
      stereo->set_right_camera( right_camera );
    } else {
      stereo->set_left_camera( left_fisheye );
      stereo->set_right_camera( right_fisheye );
    }
    stereo->use_parallel_viewing();
  } else if ( choice == B ) {
    if ( figure != 16 ) {
      stereo->set_left_camera( right_camera );
      stereo->set_right_camera( left_camera );
    } else {
      stereo->set_left_camera( right_fisheye );
      stereo->set_right_camera( left_fisheye );
    }
    stereo->use_transverse_viewing();
  } else {
    throw new std::invalid_argument( "invalid choice\n" );
  }

  stereo->set_pixel_gap( 5 );
  if ( figure == 12 ) {
    stereo->set_eye( 5, 0, 100 );
    stereo->set_lookat( 0 );
  } else if ( figure == 13 ) {
    stereo->set_eye( -2, 0, 5 );
    stereo->set_lookat( 0 );
  } else if ( figure == 14 ) {
    stereo->set_eye( 1.5, 1.75, 3 );
    stereo->set_lookat( -0.1, -0.2, 0 );
  } else if ( figure == 16 ) {
    stereo->set_eye( -150, 1000, -500 );
    stereo->set_lookat( -160, 300, -550 );
    //        stereo->set_up_vector(Vector3D(1, 0, 0));
  }

  stereo->compute_uvw();
  if ( figure == 12 ) {
    stereo->set_stereo_angle( 0.75 );    // deg, not radians
  } else {
    stereo->set_stereo_angle( 5.0 );
  }
  stereo->setup_cameras();
  w->set_camera( stereo );

  Directional *lt = new Directional;
  lt->set_direction( 100, 100, 100 );
  lt->scale_radiance( 3 );
  lt->set_shadows( true );
  w->add_light( lt );
}

void build_figure_12_12_world( World *w, CHOICE choice ) {
  std::vector<ColorCenterRadius> spheres = {
    {    cyan,   Point3D( 0, 0,  35 ), 0.75},
    {redBrown,   Point3D( 0, 0,   0 ),    2},
    {  yellow, Point3D( 1.5, 0, -80 ),    2}
  };
  build_spheres_helper( w, spheres );

  build_stereo( w, 12, choice );
}

void build_figure_12_13_world( World *w, CHOICE choice ) {
  Directional *light = new Directional;
  light->set_direction( Vector3D( 20, 30, 40 ) );
  light->scale_radiance( 2.5 );
  light->set_shadows( true );
  w->add_light( light );

  Point3D p0( -1.0 );
  Point3D p1( 1.0 );
  float   bevel_radius = 0.04;

  int i = -1;
  build_wireframe_helper( w, Point3D( i, i, i ), Point3D( i + 2, i + 2, i + 2 ), lightGrey, bevel_radius );

  build_stereo( w, 13, choice );
}

void build_figure_12_14_world( World *w, CHOICE choice ) {
  Directional *light = new Directional;
  light->set_direction( Vector3D( 20, 30, 40 ) );
  light->scale_radiance( 2.5 );
  light->set_shadows( true );
  w->add_light( light );

  Point3D p0( -1.0 );
  Point3D p1( 1.0 );
  float   bevel_radius = 0.04;

  int i = -1;
  build_wireframe_helper( w, Point3D( i, i, i ), Point3D( i + 2, i + 2, i + 2 ), lightGrey, bevel_radius );

  build_stereo( w, 14, choice );
}

void build_figure_12_16_world( World *w, CHOICE choice ) {
  Ambient *ambient = new Ambient;
  ambient->scale_radiance( 0.567 );
  w->set_ambient_light( ambient );

  PointLight *light = new PointLight;
  light->set_location( 1500, 750, 250 );
  light->scale_radiance( 4.5 );
  light->set_shadows( true );
  w->add_light( light );

  // box materials
  std::shared_ptr<Matte> matte1 = std::make_shared<Matte>();
  matte1->set_cd( 0, 0.5, 0.5 );    // cyan
  matte1->set_ka( 0.8 );
  matte1->set_kd( 0.3 );

  std::shared_ptr<Matte> matte2 = std::make_shared<Matte>();
  matte2->set_cd( 1, 0, 0 );    // red
  matte2->set_ka( 0.8 );
  matte2->set_kd( 0.3 );

  std::shared_ptr<Matte> matte3 = std::make_shared<Matte>();
  matte3->set_cd( 1, 1, 0 );    // yellow
  matte3->set_ka( 0.8 );
  matte3->set_kd( 0.3 );

  Grid *grid      = new Grid;
  int   num_boxes = 11;
  float wx = 50, wz = 50, h = 500, s = 100;

  for ( int j = 0; j < num_boxes; j++ ) {
    Box *box = new Box( Point3D( -wx, 0, -( j + 1 ) * wz - j * s ), Point3D( 0, h, -j * wz - j * s ) );
    box->set_material( matte1 );
    grid->add_object( box );
    w->add_object( box );
  }

  h = 600;
  for ( int j = 0; j < num_boxes; j++ ) {
    Box *box = new Box( Point3D( -wx - wx - s, 0, -( j + 1 ) * wz - j * s ), Point3D( -wx - s, h, -j * wz - j * s ) );
    box->set_material( matte2 );
    grid->add_object( box );
  }

  h = 750;
  for ( int j = 0; j < num_boxes; j++ ) {
    Box *box =
        new Box( Point3D( -wx - 2 * wx - 2 * s, 0, -( j + 1 ) * wz - j * s ), Point3D( -2 * wx - 2 * s, h, -j * wz - j * s ) );
    box->set_material( matte3 );
    grid->add_object( box );
  }

  grid->setup_cells();
  w->add_object( grid );

  //    Checker3D* checker_ptr = new Checker3D;
  //    checker_ptr->set_size(6 * wx);
  //    checker_ptr->set_color1(0.7);
  //    checker_ptr->set_color2(white);

  //    std::shared_ptr<SV_Matte> sv_matte = std::make_shared<SV_Matte>();
  //    sv_matte->set_ka(0.20);
  //    sv_matte->set_kd(0.50);
  //    sv_matte->set_cd(checker_ptr);
  Plane *plane = new Plane( Point3D( 0, 1, 0 ), Normal( 0, 1, 0 ) );
  //    plane_ptr->set_material(sv_matte);
  build_checkerboard( plane, white, grey, 6 * wx );
  w->add_object( plane );

  build_stereo( w, 16, choice );
}

void build_figure_12_17_world( World *w, CHOICE choice ) {
  int num_samples = 1;
  w->vp.set_pixel_size( 1.0 );

  AmbientOccluder *ambient_occluder = new AmbientOccluder;
  ambient_occluder->set_sampler( new MultiJittered( num_samples ) );
  ambient_occluder->set_min_amount( 0.5 );
  w->set_ambient_light( ambient_occluder );

  Fisheye *left_camera = new Fisheye;
  left_camera->set_fov( 180 );
  //    left_camera->set_vertical_fov(180);

  Fisheye *right_camera = new Fisheye;
  right_camera->set_fov( 180 );
  //    right_camera->set_vertical_fov(180);

  StereoCamera *stereo = new StereoCamera;
  //    stereo->set_eye(10, 15, 53);
  stereo->set_eye( 10, 15, 13 );
  stereo->set_lookat( 34, 15, 0 );

  PointLight *light = new PointLight;
  light->set_location( 150, 500, 300 );
  light->scale_radiance( 3.75 );
  light->set_shadows( true );
  w->add_light( light );

  // city parameters
  float a           = 10;        // city block width:  xw extent
  float b           = 12;        // city block length:  yw extent
  int   num_rows    = 10;        // number of blocks in the xw direction
  int   num_columns = 12;        // number of blocks in the zw direction
  float width       = 7;         // building width: xw extent in range [min, a - offset]
  float length      = 7;         // building length: zw extent in range [min, b - offset]
  float min_size    = 6;         // mininum building extent in xw and yw directions
  float offset      = 1.0;       // half the minimum distance between buildings
  float min_height  = 0.0;       // minimum building height
  float max_height  = 30;        // maximum bulding height
  float height;                  // the building height in range [min_height, max_height]
  int   num_park_rows    = 4;    // number of blocks of park in xw direction
  int   num_park_columns = 6;    // number of blocks of park in xw direction
  int   row_test;                // there are no buildings in the park
  int   column_test;             // there are no buildings in the park
  float min_color = 0.1;         // prevents black buildings
  float max_color = 0.9;         // prevents white buildings

  set_rand_seed( 15 );    // as the buildings' dimensions and colors are random, it's necessary to
                          // seed rand to keep these quantities the same at each run
                          // if you leave this out, and change the number of samples per pixel,
                          // these will change

  // the buildings are stored in a grid

  Grid *grid = new Grid;

  for ( int r = 0; r < num_rows; r++ )           // xw direction
    for ( int c = 0; c < num_columns; c++ ) {    // zw direction
      // determine if the block is in the park

      if ( ( r - num_rows / 2 ) >= 0 ) {
        row_test = r - num_rows / 2;
      } else {
        row_test = r - num_rows / 2 + 1;
      }
      if ( ( c - num_columns / 2 ) >= 0 ) {
        column_test = c - num_columns / 2;
      } else {
        column_test = c - num_columns / 2 + 1;
      }

      if ( abs( row_test ) >= ( num_park_rows / 2 ) || abs( column_test ) >= ( num_park_columns / 2 ) ) {
        std::shared_ptr<Matte> matte = std::make_shared<Matte>();
        matte->set_ka( 0.4 );
        matte->set_kd( 0.6 );
        matte->set_cd( min_color + rand_float() * ( max_color - min_color ),
                       min_color + rand_float() * ( max_color - min_color ),
                       min_color + rand_float() * ( max_color - min_color ) );

        // block center coordinates
        float xc = a * ( r - num_rows / 2.0 + 0.5 );
        float zc = b * ( c - num_columns / 2.0 + 0.5 );

        width  = min_size + rand_float() * ( a - 2 * offset - min_size );
        length = min_size + rand_float() * ( b - 2 * offset - min_size );

        // minimum building coordinates
        float xmin = xc - width / 2.0;
        float ymin = 0.0;
        float zmin = zc - length / 2.0;

        // maximum building coordinates
        height = min_height + rand_float() * ( max_height - min_height );

        // The following is a hack to make the middle row and column of buildings higher
        // on average than the other buildings.
        // This only works properly when there are three rows and columns of buildings
        if ( r == 1 || r == num_rows - 2 || c == 1 || c == num_columns - 2 ) height *= 1.5;

        float xmax = xc + width / 2.0;
        float ymax = height;
        float zmax = zc + length / 2.0;

        Box *building = new Box( Point3D( xmin, ymin, zmin ), Point3D( xmax, ymax, zmax ) );
        building->set_material( matte );
        grid->add_object( building );
      }
    }

  grid->setup_cells();
  w->add_object( grid );

  // render the park with small green checkers
  Box *park = new Box( Point3D( -a * num_park_rows / 2, 0.0, -b * num_park_columns / 2 ),
                       Point3D( a * num_park_rows / 2, 0.1, b * num_park_columns / 2 ) );
  build_checkerboard( park, RGBColor( 0.35, 0.75, 0.35 ), RGBColor( 0.3, 0.5, 0.3 ), 5 );
  w->add_object( park );

  // ground plane with checker:
  Plane *plane = new Plane( Point3D( 0, 0.01, 0 ), Normal( 0, 1, 0 ) );
  build_checkerboard( plane, RGBColor( 0.7 ), RGBColor( 0.3, 0.5, 0.3 ), 50 );
  w->add_object( plane );

  Image *image = new Image;
  image->read_ppm_file( "/Users/williammccarthy/Downloads/__484/qt/RT_sparkle_shadows/ppm_images/blue_sky_dense.ppm" );

  SphericalMap *spherical_map = new SphericalMap;

  ImageTexture *image_texture = new ImageTexture( image );
  image_texture->set_mapping( spherical_map );

  std::shared_ptr<SV_Matte> sv_matte = std::make_shared<SV_Matte>();
  sv_matte->set_ka( 1.0 );
  sv_matte->set_kd( 0.85 );
  //    sv_matte->set_cd(RGBColor(1, 0, 0));
  sv_matte->set_cd( image_texture );

  Instance *sphere = new Instance( new Sphere() );
  sphere->scale( 1000000 );
  sphere->set_material( sv_matte );
  sphere->set_shadows( false );    // reguired for ambient occlusion to work
  w->add_object( sphere );

  build_stereo( w, 17, choice );
}
