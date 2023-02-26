#include "SV_Lambertian.h"


SV_Lambertian::SV_Lambertian(void)
: BRDF(),
  kd(0.0),
  cd(NULL) 
{ }



SV_Lambertian::SV_Lambertian(const SV_Lambertian& other)
: BRDF() { copy(other); } 



SV_Lambertian& SV_Lambertian::operator=(const SV_Lambertian& other) {
    if (this != &other) { copy(other); }
    return (*this);
}



void SV_Lambertian::copy(const SV_Lambertian& other) {
    BRDF::operator= (other);

    kd = other.kd;
    Texture* ptext = other.cd;
    cd = ptext ? ptext->clone() : NULL;
}



SV_Lambertian::~SV_Lambertian(void) {
    if (cd) { delete cd; }
}



SV_Lambertian* SV_Lambertian::clone(void) const {
    return new SV_Lambertian(*this);
}



RGBColor SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& /*wo*/) const {
    return kd * cd->get_color(sr);
}


RGBColor SV_Lambertian::f(const ShadeRec& sr, const Vector3D& /*wo*/, const Vector3D& /*wi*/) const {
    return kd * cd->get_color(sr) *invPI;
}


RGBColor SV_Lambertian::sample_f(const ShadeRec& sr, const Vector3D& /*wo*/, Vector3D& wi, float& pdf) const {
  Vector3D w = sr.normal;
  Vector3D v = Vector3D(0.0034, 1, 0.0071).cross(w);
  v.normalize();
  Vector3D u = v.cross(w);

  Point3D sp = sampler_ptr->sample_hemisphere();
  wi = sp.x * u + sp.y * v + sp.z * w;
  wi.normalize();

  pdf = sr.normal.dot(wi) * invPI;

  return (kd * cd->get_color(sr) * invPI);
}
