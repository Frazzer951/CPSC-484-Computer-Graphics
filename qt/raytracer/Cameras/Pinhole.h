#ifndef __PINHOLE__
#define __PINHOLE__

#include "Utilities/Point2D.h"
#include "World/World.h"    // we can #include "World.h" here



//=====================================
// Pinhole
//=====================================
//
class Pinhole: public Camera {
public:
    Pinhole() :	Camera(), d(500), zoom(1.0) { }
    Pinhole(const Pinhole& c)  : Camera(c), d(c.d), zoom(c.zoom) { }

    Pinhole& operator= (const Pinhole& rhs) {
        if (this == &rhs) { return (*this); }
        Camera::operator= (rhs);
        d = rhs.d;
        zoom = rhs.zoom;
        return (*this);
    }
    virtual ~Pinhole() { }
    virtual Camera*	clone() const { return (new Pinhole(*this)); }

    void set_view_distance(const float vpd) { d = vpd; }
    void set_zoom(const float zoom_factor)  { zoom = zoom_factor; }
    Vector3D get_direction(const Point2D& p) const {
        Vector3D dir = p.x * u + p.y * v - d * w;
        dir.normalize();
        return(dir);
    }

    virtual void render_scene(const World& w);

private:
    float	d;		// view plane distance
    float	zoom;	// zoom factor
};


#endif
