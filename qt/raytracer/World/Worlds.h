#ifndef WORLDS_H
#define WORLDS_H

#include "World.h"

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
#include "GeometricObjects/PartObjects/PartAnnulus.h"

#include "GeometricObjects/Triangles/Triangle.h"

#include "GeometricObjects/Primitives/Plane.h"
#include "GeometricObjects/Primitives/Torus.h"

#include "Lights/Directional.h"
#include "Lights/PointLight.h"
#include "Lights/AmbientOccluder.h"

#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "Materials/Reflective.h".

#include "Textures/Checker3D.h"
#include "Textures/ImageTexture.h"

#include "Samplers/MultiJittered.h"
#include "Samplers/Jittered.h"

#include "Tracers/RayCast.h"

#include "Mappings/SphericalMap.h"

#include "World/Worlds.h"

enum CHOICE { A, B, C, D, E, F };

void build_cone_helper( World *w, const Point3D &posn, const RGBColor &color, double h, double r );
void build_cylinder_helper( World *w, const Point3D &posn, const RGBColor &color, double b, double t, double r,
                            Vector3D rotation = { 90, 0, 0 } );

//void build_spheres( World *w );
void build_sphere_world( World *w );

//void build_city( World *w );
void build_city_world( World *w, double distance = 800.0 );

void build_practical( World *w );
void build_practical_world( World *w, double distance = 130.0 );

//void build_sphere_triangle_box(World* w);
void build_sphere_triangle_box_world( World *w, CHOICE choice );

//void build_olympic_rings(World* w);
void build_olympic_rings_world( World *w );

//void build_thinlens(World* w, double focal_distance);
void build_figure_10_10( World *w, CHOICE choice );

//void build_fisheye(World* w, CHOICE choice);
void build_figure_11_7( World *w, CHOICE choice );

//void build_stereographic(World* w, double focal_distance);
//void build_figure_12_12(World* w, CHOICE choice);

//void build_mcdonalds(World* w);
void build_mcdonalds_world( World *w );
//void build_mcdonalds_alberto(World* w);

//void build_sundial(World* w, double radius);
//void build_sundial_world(World* w, double radius);

//void build_sundial(World* w, double height=6.0, double radius=20.0, double lat=30.0);
//void build_sundial_world(World* w, double height=6.0, double radius=20.0, double lat=30.0);

//void build_voyager(World* w);
//void build_voyager_world(World* w);

//void build_reflective_and_transparent_sphere(World* w, int fig);

//void build_five_reflective_transparent_spheres(World* w);

//void build_sundial(World* w, double radius);

//void build_discussion( World *w );
void build_discussion_world( World *w );

//void build_stonehenge( World *w );
void build_stonehenge_world( World *w );

//void build_figure_12( World *w, int number );
void build_figure_12_world( World *w, int number );

#endif    // WORLDS_H
