#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "BRDFs/Lambertian.h"


//=====================================
// Matte
//=====================================
//
class Matte: public Material {
public:
    Matte();
    Matte(const Matte& m);
    Matte& operator= (const Matte& rhs);

    ~Matte();
    virtual Material* clone(void) const;

    // there is no Lambertian::ka data member because ambient reflection
    // is diffuse reflection
    void set_ka(const float ka);

    // this also sets Lambertian::kd, but for a different Lambertian object
    void set_kd(const float kd);

    void set_cd(const RGBColor c);
    void set_cd(const float r, const float g, const float b);
    void set_cd(const float c);


    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);

private:
    Lambertian*	ambient_brdf;
    Lambertian*	diffuse_brdf;
};


#endif
