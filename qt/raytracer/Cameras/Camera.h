#ifndef __CAMERA__
#define __CAMERA__

// There is no view plane distance because the fisheye and panoramic cameras don't use it

#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"

struct World;  // can't #include "World" here because World contains a camera pointer


//=====================================
// Camera
//=====================================
//
class Camera {
public:
    Camera();

    Camera(const Camera& camera);    // rule of 3
protected:
    Camera& operator= (const Camera& camera);
public:
    virtual ~Camera() {}

    virtual Camera* clone() const = 0;

    virtual void render_scene(const World& w) = 0;

    void set_eye(const Point3D& p)  {  eye = p;  }
    void set_eye(const float x, const float y, const float z) {
        eye.x = x; eye.y = y; eye.z = z;
    }

    void set_lookat(const Point3D& p) { lookat = p; }
    void set_lookat(const float x, const float y, const float z) {
        lookat.x = x; lookat.y = y; lookat.z = z;
    }

    void set_up_vector(const Vector3D& u) { up = u; }
    void set_up_vector(const float x, const float y, const float z) {
        up.x = x; up.y = y; up.z = z;
    }
    Vector3D get_up_vector() const { return up; }

    void set_roll(const float r) { ra = r; }

    void set_exposure_time(const float exposure) {
        exposure_time = exposure;
    }

    void compute_uvw();

protected:
    Point3D	  eye;		// eye point
    Point3D	  lookat; 	// lookat point
    float	  ra;		// roll angle
    Vector3D  u, v, w;	// orthonormal basis vectors
    Vector3D  up;		// up vector
    float	  exposure_time;
};


#endif
