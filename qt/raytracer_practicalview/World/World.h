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

class RenderThread; 	//part of skeleton - wxRaytracer.h
class RenderCanvas;


//=====================================
// World
//=====================================
//
struct World {
public:
    World();
    ~World();

    void add_object(GeometricObject* object_ptr) { objects.push_back(object_ptr); }
    void add_light(Light* light_ptr)             { lights.push_back(light_ptr); }

    void set_ambient_light(Light* light_ptr)     { ambient_ptr = light_ptr; }
    void set_camera(Camera* c_ptr)               { camera_ptr = c_ptr; }


    void build();
    void render_scene() const;
    void render_perspective() const;

    RGBColor max_to_one(const RGBColor& c) const;
    RGBColor clamp_to_color(const RGBColor& c) const;


    void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;
    ShadeRec hit_objects(const Ray& ray);
                 // next function ONLY in chapter 3:  bare-bones ray tracing
//    ShadeRec hit_bare_bones_objects(const Ray& ray);

private:
    void delete_objects();
    void delete_lights();
    void add_sphere_helper(RGBColor color, Point3D pt, int radius);
    void add_bb_helper(RGBColor color, Point3D pt1, Point3D pt2, double r=0.1);
    void add_rect_helper(RGBColor color, Point3D pt, Vector3D pt1, Vector3D pt2,
                         Normal n);
    void add_triangle_helper(RGBColor color, Point3D pt0, Point3D pt1, Point3D pt2);

    void build_spheres(void);
//    void init_cameras();
    void init_cameras(Point3D eye, Point3D lookat, double view_distance, Point3D up);
    void init_viewplane(void);
    void init_light(void);
    void init_plane(void);
    void init_environment(Point3D eye=Point3D(-0.5, 0, 70), Point3D lookat=Point3D(-0.5, 0, 10),
                          double view_distance=800.0, Point3D up=Point3D(0, 1, 0));

    void set_material(GeometricObject* geo, RGBColor color);

    void checkerboard_row(RGBColor color1, RGBColor color2, int y, int xmin, int xmax, int z);
    void build_checkerboard(RGBColor c1, RGBColor c2, int xmin=-10, int ymin=-10, int xmax=10, int ymax=10, int z=0);
    void build_practical();
    void build_city(void);

public:
    ViewPlane	vp;
    RGBColor	background_color;
    Tracer*		tracer_ptr;

    Light*   	ambient_ptr;
    Camera*		camera_ptr;
    Sphere 		sphere;		// for Chapter 3 only

    std::vector<GeometricObject*>	objects;
    std::vector<Light*> 			lights;

    RenderThread* 	paintArea; 	//connection to skeleton - wxRaytracer.h
    RenderCanvas*   canvas;
};


#endif
