#ifndef __AMBIENT__
#define __AMBIENT__

#include "Lights/Light.h"


//=====================================
// Ambient
//=====================================
//
class Ambient: public Light {
public:
    Ambient();

    Ambient(const Ambient& a);
    Ambient& operator= (const Ambient& rhs);
    virtual ~Ambient();

    virtual Light* clone() const;

    void scale_radiance(const float b);

    void set_color(const float c);
    void set_color(const RGBColor& c);
    void set_color(const float r, const float g, const float b);


    virtual Vector3D get_direction(ShadeRec& s);

    virtual RGBColor L(ShadeRec& s);

private:
    float		ls;
    RGBColor	color;
};


#endif
