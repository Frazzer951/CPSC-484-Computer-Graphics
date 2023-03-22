#include "World.h"

#include "Cameras/Pinhole.h"

#include "GeometricObjects/GeometricObject.h"
#include "GeometricObjects/Primitives/Rectangle.h"
#include "GeometricObjects/BeveledObjects/BeveledBox.h"
#include "GeometricObjects/Triangles/Triangle.h"
#include "GeometricObjects/Instance.h"

#include "World/World_builder.h"
#include "Textures/Checker3D.h"
#include "Materials/SV_Matte.h"
#include "Materials/Phong.h"

#include "Lights/Directional.h"
#include "Lights/PointLight.h"
#include "Tracers/Whitted.h"

void set_environment( World *w, int fig ) {    // 130 for 13.a, 131 for 13.b, 132 for 13.c
  int num_samples = 16;

  w->vp.set_hres( 600 );
  w->vp.set_vres( 600 );
  w->vp.set_samples( num_samples );

  //    w->vp.set_max_depth(2);			// for Figure 27.13(a)
  //	w->vp.set_max_depth(4);			// for Figure 27.13(b)
  int depth = 5;
  switch ( fig ) {
  case 12:
  case 132:
  case 140:
  case 141:
  case 15: depth = 5; break;
  case 130: depth = 2; break;
  case 131: depth = 4; break;
  default: depth = 5; break;
  }

  w->vp.set_max_depth( depth );    // for Figure 27.12, 27.13(c), 27.14a/b, 27.15b

  w->background_color = RGBColor( 0.0, 0.3, 0.25 );

  w->tracer_ptr = new Whitted( w );
}

void set_cameras_lights( World *w, int fig ) {
  w->background_color = RGBColor( 0.0, 0.3, 0.25 );

  w->tracer_ptr = new Whitted( w );

  Ambient *ambient_ptr = new Ambient;
  ambient_ptr->scale_radiance( 0.25 );
  w->set_ambient_light( ambient_ptr );

  Pinhole *pinhole_ptr = new Pinhole;

  // camera setup for the top down view, Figure 7.2 with maxDepth = 5 and eta = 1.5
  if ( fig == 12 ) {
    pinhole_ptr->set_eye( 2.0, 50.0, -3.0 );    // 27.12
    pinhole_ptr->set_lookat( 2.0, 0.0, -3.0 );
    pinhole_ptr->set_view_distance( 1800.0 );
  } else {
    pinhole_ptr->set_eye( -8, 5.5, 40 );
    pinhole_ptr->set_lookat( 1, 4, 0 );
    pinhole_ptr->set_view_distance( 2400.0 );
  }
  pinhole_ptr->compute_uvw();
  w->set_camera( pinhole_ptr );

  // point light
  PointLight *light_ptr1 = new PointLight;
  light_ptr1->set_location( 40, 50, 0 );
  light_ptr1->scale_radiance( 19.5 );
  light_ptr1->set_shadows( true );
  w->add_light( light_ptr1 );

  // point light
  PointLight *light_ptr2 = new PointLight;
  light_ptr2->set_location( -10, 20, 10 );
  light_ptr2->scale_radiance( 19.5 );
  light_ptr2->set_shadows( true );
  w->add_light( light_ptr2 );

  // directional light
  Directional *light_ptr3 = new Directional;
  light_ptr3->set_direction( -1, 0, 0 );
  light_ptr3->scale_radiance( 19.5 );
  light_ptr3->set_shadows( true );
  w->add_light( light_ptr3 );
}

void add_sphere_helper( World *w, RGBColor color, Point3D pt, double radius ) {
  Sphere *s = new Sphere( pt, radius );
  w->set_material( s, color );
  w->add_object( s );
}

void add_bb_helper( World *w, RGBColor color, Point3D p0, Point3D p1, double r ) {
  BeveledBox *bb = new BeveledBox( p0, p1, r );
  w->set_material( bb, color );
  w->add_object( bb );
}

void add_bb_helper( World *w, RGBColor color, Point3D p0, double dx, double dy, double dz ) {
  add_bb_helper( w, color, p0, Point3D( p0.x + dx, p0.y + dy, p0.z + dz ) );
}

void add_bb_helper( World *w, RGBColor color, Point3D p0, double dx, double dy, double dz, double rot_x, double rot_y,
                    double rot_z, double radius ) {
  BeveledBox *bb      = new BeveledBox( Point3D( 0 ), Point3D( dx, dy, dz ), radius );
  Instance   *bev_box = new Instance( bb );
  bev_box->rotate_x( rot_x );
  bev_box->rotate_y( rot_y );
  bev_box->rotate_z( rot_z );
  bev_box->translate( p0 );
  w->set_material( bev_box, color );
  w->add_object( bev_box );
}

void add_rect_helper( World *w, RGBColor color, Point3D pt, Vector3D pt1, Vector3D pt2, Normal n ) {
  // front face: +ve z
  class Rectangle *ff = new class Rectangle( pt, pt1, pt2, n );
  w->set_material( ff, color );
  w->add_object( ff );
}

void add_triangle_helper( World *w, RGBColor color, Point3D pt0, Point3D pt1, Point3D pt2 ) {
  // front face: +ve z
  Triangle *t = new Triangle( pt0, pt1, pt2 );

  std::shared_ptr<Phong> phong = std::make_shared<Phong>();
  phong->set_ka( 0.25 );
  phong->set_kd( 0.75 );
  phong->set_cd( color );
  phong->set_ks( 0.25 );
  phong->set_exp( 1.5 );

  t->set_material( phong );
  w->add_object( t );
}

void build_axis( World *w, RGBColor color_triangle, RGBColor color_axis, double length, double width ) {
  add_bb_helper( w, Qt::red, Point3D( 0, 0, 0 ), length, width, width );
  add_triangle_helper( w, color_triangle, Point3D( length, 0, 1.2 * width ), Point3D( length, 0, -0.6 * width ),
                       Point3D( length + 1.2 * width, 0, 0.6 * width ) );

  add_bb_helper( w, color_axis, Point3D( 0, 0, 0 ), width, length, width );
  add_triangle_helper( w, color_axis, Point3D( 0, length, 1.2 * width ), Point3D( 0, length, -0.6 * width ),
                       Point3D( 0, length + 1.2 * width, 0.6 * width ) );
}

void build_checkerboard( GeometricObject *p_geo, RGBColor c1, RGBColor c2, double size ) {
  Checker3D *p_checker = new Checker3D;
  p_checker->set_size( size );
  p_checker->set_color1( c1 );
  p_checker->set_color2( c2 );

  //    SV_Matte* p_matte = new SV_Matte();
  std::shared_ptr<SV_Matte> p_matte = std::make_shared<SV_Matte>();
  p_matte->set_ka( 0.75 );
  p_matte->set_kd( 0.75 );
  p_matte->set_cd( p_checker );

  p_geo->set_material( p_matte );
}
