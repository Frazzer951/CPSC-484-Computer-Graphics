#include "SV_Matte.h"

// ---------------------------------------------------------------- default constructor

SV_Matte::SV_Matte (void):
  Material(),
  ambient_brdf(new SV_Lambertian),
  diffuse_brdf(new SV_Lambertian) {
}

// ---------------------------------------------------------------- copy constructor
SV_Matte::SV_Matte(const SV_Matte& other) 
: SV_Matte() { copy(other); }

// ---------------------------------------------------------------- assignment operator
SV_Matte& SV_Matte::operator= (const SV_Matte& other) {
    if (this != &other) { copy(other); }
    return *this;
}

void SV_Matte::copy(const SV_Matte& other) {
    Material::operator=(other);

    SV_Lambertian* pamb = other.ambient_brdf;
    SV_Lambertian* pdiff = other.diffuse_brdf;

    ambient_brdf = pamb ? pamb->clone() : NULL;
    diffuse_brdf = pdiff ? pdiff->clone() : NULL;
}

// ---------------------------------------------------------------- destructor
SV_Matte::~SV_Matte(void) {
    if (ambient_brdf) { delete ambient_brdf; }
    if (diffuse_brdf) { delete diffuse_brdf; }
}

// ---------------------------------------------------------------- clone
SV_Matte* SV_Matte::clone(void) const { return new SV_Matte(*this); }

// ---------------------------------------------------------------- shade
RGBColor SV_Matte::shade(ShadeRec& sr) {
  Vector3D 	wo 			= -sr.ray.d;
  RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
  int 		num_lights	= sr.w.lights.size();

  for (int j = 0; j < num_lights; j++) {
    Light* light_ptr = sr.w.lights[j];
    Vector3D wi = light_ptr->get_direction(sr);
    wi.normalize();
    float ndotwi = sr.normal.dot(wi);
    float ndotwo = sr.normal.dot(wo);

    if (ndotwi > 0.0 && ndotwo > 0.0) {
      bool in_shadow = false;

      if (light_ptr->cast_shadows()) {
        Ray shadowsRay(sr.hit_point, wi);
        in_shadow = light_ptr->in_shadow(shadowsRay, sr);
      }

      if (!in_shadow)
        L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
    }
  }

  return L;
}

#include <QDebug>
RGBColor SV_Matte::area_light_shade(ShadeRec& sr) {
  //qDebug() << "SV_Matte::area_light_shade";
  Vector3D 	wo 			= -sr.ray.d;
  RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
  int num_lights	= sr.w.lights.size();

  for (int j = 0; j < num_lights; j++) {
    Vector3D wi = sr.w.lights[j]->get_direction(sr);
    float ndotwi = sr.normal.dot(wi);
    float ndotwo = sr.normal.dot(wo);

    if (ndotwi > 0.0 && ndotwo > 0.0) {
      bool in_shadow = false;

      if (sr.w.lights[j]->cast_shadows()) {
        Ray shadow_ray(sr.hit_point, wi);
        in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
      }

      if (!in_shadow)
        L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
    }
  }

  return (L);
}
