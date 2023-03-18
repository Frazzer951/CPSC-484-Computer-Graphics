//#include "World.h"

//#include "Cameras/Pinhole.h"

//#include "GeometricObjects/GeometricObject.h"
//#include "GeometricObjects/Primitives/Rectangle.h"
//#include "GeometricObjects/BeveledObjects/BeveledBox.h"
//#include "GeometricObjects/Triangles/Triangle.h"

//#include "World/World_builder.h"
//#include "Textures/Checker3D.h"
//#include "Materials/SV_Matte.h"
//#include "Materials/Matte.h"

//#include "Lights/Directional.h"
//#include "Lights/PointLight.h"
//#include "Tracers/Whitted.h"

//void create_floor_rect(World* w, int fig) {
//    Checker3D* checker_ptr = new Checker3D;
//    checker_ptr->set_size(4);
//    checker_ptr->set_color1(0.75);
//    checker_ptr->set_color2(white);

//    SV_Matte* sv_matte_ptr = new SV_Matte;
//    sv_matte_ptr->set_ka(0.5);
//    sv_matte_ptr->set_kd(0.35);
//    sv_matte_ptr->set_cd(checker_ptr);

//    // rectangle
//    Rectangle* rectangle_ptr;

//    if (fig == 12 || fig == 15) {
//        rectangle_ptr = new Rectangle(Point3D(-20, -0.001, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
//    } else {
//        Point3D p0(-20, 0, -100);
//        Vector3D a(0, 0, 120);       // Fig. 13, 14
//        Vector3D b(40, 0, 0);

//        rectangle_ptr = new Rectangle(p0, a, b);
//    }

//    rectangle_ptr->set_material(sv_matte_ptr);
//    w->add_object(rectangle_ptr);
//}

////void ray_tracing_worlds_16(World* w) {
////    int num_samples = 25;

////    w->vp.set_hres(600);
////    w->vp.set_vres(400);
////    w->vp.set_samples(num_samples);

////    w->tracer_ptr = new RayCast(w);

////    Pinhole* camera_ptr = new Pinhole;

////    // for Figure 16.5(a)
////    camera_ptr->set_eye(350, 1000, 500);
////    camera_ptr->set_lookat(-175, 550, -40);
////    camera_ptr->set_view_distance(350);

/////*
////    // for Figure 16.5(b)
////    camera_ptr->set_eye(1500, 750, 250);
////    camera_ptr->set_lookat(-50, 300, -600);
////    camera_ptr->set_view_distance(650);
////*/
////    camera_ptr->compute_uvw();
////    w->set_camera(camera_ptr);

////    PointLight* light_ptr = new PointLight;
////    light_ptr->set_location(1500, 750, 250);
////    light_ptr->scale_radiance(4.5);
////    light_ptr->set_shadows(true);
////    w->add_light(light_ptr);

////    // box materials
////    Matte* matte_ptr1 = new Matte;
////    matte_ptr1->set_cd(0, 0.5, 0.5);     // cyan
////    matte_ptr1->set_ka(0.4);
////    matte_ptr1->set_kd(0.5);

////    Matte* matte_ptr2 = new Matte;
////    matte_ptr2->set_cd(1, 0, 0);     	  // red
////    matte_ptr2->set_ka(0.4);
////    matte_ptr2->set_kd(0.5);

////    Matte* matte_ptr3 = new Matte;
////    matte_ptr3->set_cd(0.5, 0.6, 0);     // green
////    matte_ptr3->set_ka(0.4);
////    matte_ptr3->set_kd(0.5);

////    // Construct rows of boxes stored in a grid
////    Grid* grid_ptr = new Grid;
////    // first row
////    int num_boxes = 11;
////    float wx = 50;
////    float wz = 50;
////    float h = 300;
////    float s = 100;

////    for (int j = 0; j < num_boxes; j++) {
////        Box* box_ptr = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s),
////                                Point3D(0, h, - j * wz - j * s));
////        box_ptr->set_material(matte_ptr1);
////    //	add_object(box_ptr);
////        grid_ptr->add_object(box_ptr);
////    }

////    // second row
////    h = 450;
////    for (int j = 0; j <= num_boxes; j++) {
////        Box* box_ptr = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s),
////                                Point3D(-wx - s, h, - j * wz - j * s));
////        box_ptr->set_material(matte_ptr2);
//////		add_object(box_ptr);
////        grid_ptr->add_object(box_ptr);
////    }

////    // third row
////    h = 600;
////    for (int j = 0; j <= num_boxes; j++) {
////        Box* box_ptr = new Box(	Point3D(-wx - 2 * wx - 2 * s, 0, -(j + 1) * wz - j * s),
////                                Point3D(-2 * wx - 2 * s, h, - j * wz - j * s));
////        box_ptr->set_material(matte_ptr3);
//////		add_object(box_ptr);
////        grid_ptr->add_object(box_ptr);
////    }

////    grid_ptr->setup_cells();
////    w->add_object(grid_ptr);

////    // ground plane with checker
////    Checker3D* checker_ptr = new Checker3D;
////    checker_ptr->set_size(wx);
////    checker_ptr->set_color1(0.7);
////    checker_ptr->set_color2(white);

////    SV_Matte* sv_matte_ptr1 = new SV_Matte;
////    sv_matte_ptr1->set_ka(0.15);
////    sv_matte_ptr1->set_kd(1.0);
////    sv_matte_ptr1->set_cd(checker_ptr);
////    Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
////    plane_ptr->set_material(sv_matte_ptr1);
////    w->add_object(plane_ptr);
////}

//void ray_tracing_worlds_27(World* w) {
//    int fig = 140;     // fig 12, 130, 131, 132, 140, 141, or 15   130 is 13(a), 131 is 13(b), etc.

//    set_environment(w, fig);
//    set_cameras_lights(w, fig);
//    create_spheres(w, fig);
//    create_floor_rect(w, fig);

//     ray_trace_27_19a();
//     ray_trace_27_19b();
//     ray_trace_27_19c();
//     ray_trace_27_20();

//     ray_trace_27_21a();
//     ray_trace_27_21b();

//     ray_trace_27_23a();
//     ray_trace_27_23b();

//     ray_trace_27_24a();

//     ray_trace_27_26();
//     ray_trace_27_28();
//     ray_trace_27_29();
//     ray_trace_27_30();
//     ray_trace_27_32();
//}

//void ray_tracing_worlds(World* w) {
//    ray_tracing_worlds_16(w);

//    //    ray_tracing_worlds_26();
////    ray_tracing_worlds_27(w);
//}
