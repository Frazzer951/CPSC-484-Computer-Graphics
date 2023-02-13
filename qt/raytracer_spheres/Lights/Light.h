#ifndef __LIGHT__
#define __LIGHT__

#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Ray.h"

class ShadeRec;


//=====================================
// Light
//=====================================
//
class Light {
public:
    Light();
    virtual ~Light();

    Light(const Light& ls);
    Light& operator= (const Light& rhs);
    virtual Light* clone() const = 0;

    virtual Vector3D get_direction(ShadeRec& sr) = 0;
    virtual RGBColor L(ShadeRec& sr);
};

#endif
