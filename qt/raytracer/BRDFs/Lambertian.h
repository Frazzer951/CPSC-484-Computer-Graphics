#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDFs/BRDF.h"
#include "Utilities/Constants.h"


//=====================================
// Lambertian
//=====================================
//
class Lambertian: public BRDF {
public:
    Lambertian() : BRDF(), kd(0.0), cd(0.0) { }

    Lambertian(const Lambertian& lamb)
    :   BRDF(lamb), kd(lamb.kd), cd(lamb.cd) { }

    Lambertian& operator= (const Lambertian& rhs) {
        if (this != &rhs) {
            BRDF::operator=(rhs);  kd = rhs.kd;  cd = rhs.cd;
        }
        return *this;
    }
    virtual ~Lambertian() { }

    virtual Lambertian* clone() const { return (new Lambertian(*this)); }

    virtual RGBColor f(const ShadeRec&, const Vector3D&,
                       const Vector3D&) const {
        return (kd * cd * invPI);
    }
    virtual RGBColor rho(const ShadeRec&, const Vector3D&) const {
        return (kd * cd);
    }

    void set_ka(const float k)  { kd = k; }
    void set_kd(const float k)  { kd = k; }

    void set_cd(const RGBColor& c) { cd = c; }
    void set_cd(const float r, const float g, const float b) {
        cd.r = r;  cd.g = g;  cd.b = b;
    }
    void set_cd(const float c) { cd.r = cd.g = cd.b = c; }

private:
    float	  kd;
    RGBColor  cd;
};


#endif

