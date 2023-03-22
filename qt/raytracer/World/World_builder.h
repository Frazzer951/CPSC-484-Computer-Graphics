#ifndef WORLD_BUILDER_H
#define WORLD_BUILDER_H

#include "World/World.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"

void set_environment( World *w, int fig );
void set_cameras_lights( World *w, int fig );

void add_sphere_helper( World *w, RGBColor color, Point3D pt, double radius );

void add_bb_helper( World *w, RGBColor color, Point3D p0, Point3D p1, double r = 0.1 );
void add_bb_helper( World *w, RGBColor color, Point3D p0, double dx, double dy, double dz );
void add_bb_helper( World *w, RGBColor color, Point3D p0, double dx, double dy, double dz, double rot_x, double rot_y,
                    double rot_z, double radius = 0.1 );
void add_rect_helper( World *w, RGBColor color, Point3D pt, Vector3D pt1, Vector3D pt2, Normal n );
void add_triangle_helper( World *w, RGBColor color, Point3D pt0, Point3D pt1, Point3D pt2 );

void build_axis( World *w, RGBColor color_triangle, RGBColor color_axis, double length, double width );

void build_checkerboard( GeometricObject *p_geo, RGBColor c1, RGBColor c2, double size );

#endif    // WORLD_BUILDER_H
