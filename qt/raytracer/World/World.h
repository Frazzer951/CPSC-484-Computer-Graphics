#ifndef __WORLD__
#define __WORLD__

// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory.

#include <vector>

#include "Cameras/Camera.h"
#include "GeometricObjects/GeometricObject.h"
#include "GeometricObjects/Primitives/Sphere.h"
#include "Lights/Light.h"
#include "Lights/Ambient.h"
#include "Tracers/Tracer.h"
#include "Utilities/Ray.h"
#include "Utilities/RGBColor.h"
#include "World/ViewPlane.h"

#include "UserInterface/qtraytracer.h"

class RenderThread;    //part of skeleton - wxRaytracer.h
class RenderCanvas;

//=====================================
// World
//=====================================
//
struct World {
public:
  World();
  ~World();

  void add_object( GeometricObject *object_ptr ) { objects.push_back( object_ptr ); }
  void add_light( Light *light_ptr ) { lights.push_back( light_ptr ); }

  void set_ambient_light( Light *light_ptr ) { ambient_ptr = light_ptr; }
  void set_camera( Camera *c_ptr ) { camera_ptr = c_ptr; }

  void build();
  void check() {
    if ( camera_ptr == nullptr ) {
      qDebug( "World doesn't have a camera\n" );
      throw new std::logic_error( "World doesn't have a camera\n" );
    }
    if ( tracer_ptr == nullptr ) {
      qDebug( "World doesn't have a ray tracer\n" );
      throw new std::logic_error( "World doesn't have a ray tracer\n" );
    }
    if ( ambient_ptr == nullptr ) { qDebug( "World has no ambient light...\n" ); }
    if ( lights.empty() ) { qDebug( "World has no lights...\n" ); }
    if ( objects.empty() ) { qDebug( "World has no objects to display...\n" ); }
  }
  void render_scene() const;
  void render_perspective() const;

  RGBColor max_to_one( const RGBColor &c ) const;
  RGBColor clamp_to_color( const RGBColor &c ) const;

  void     display_pixel( const int row, const int column, const RGBColor &pixel_color ) const;
  ShadeRec hit_objects( const Ray &ray );

  ShadeRec hit_bare_bones_objects( const Ray &ray );    // chapter 3 only

  void init_viewplane( void );
  void init_ambient_light( double radiance = 0.2 );
  void init_plane( void );

  void set_material( GeometricObject *geo, RGBColor color );

private:
  void delete_objects();
  void delete_lights();

public:
  ViewPlane vp;
  RGBColor  background_color;
  Tracer   *tracer_ptr;

  Light  *ambient_ptr;
  Camera *camera_ptr;
  Sphere  sphere;    // for Chapter 3 only

  std::vector<GeometricObject *> objects;
  std::vector<Light *>           lights;

  RenderThread *paintArea;    //connection to skeleton - wxRaytracer.h
  RenderCanvas *canvas;
};

#endif
