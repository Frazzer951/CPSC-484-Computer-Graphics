#ifndef __BRDF__
#define __BRDF__

#include <math.h>

#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"
#include "Utilities/Constants.h"


//=====================================
// BRDF
//=====================================
//
class BRDF {
public:
    BRDF() = default;

    BRDF(const BRDF&) { }     // do nothing
protected:
    BRDF& operator= (const BRDF& rhs) {
        if (this == &rhs)
            return (*this);
        return (*this);
    }
public:
    ~BRDF() { }

    virtual BRDF* clone() const = 0;

    virtual RGBColor  f(const ShadeRec&, const Vector3D&, const Vector3D&) const {
        return black;
    }

    virtual RGBColor  sample_f(const ShadeRec&, const Vector3D&, Vector3D&) const {
        return black;
    }
    virtual RGBColor  sample_f(const ShadeRec&, const Vector3D&, Vector3D&, float&) const {
        return black;
    }

    virtual RGBColor  rho(const ShadeRec&, const Vector3D&) const { return black; }
};

#endif


