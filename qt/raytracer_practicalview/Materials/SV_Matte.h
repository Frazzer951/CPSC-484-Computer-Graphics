#ifndef SV_MATTE_H
#define SV_MATTE_H

#include "Material.h"
#include "BRDFs/SV_Lambertian.h"

class SV_Matte: public Material {
public:
  SV_Matte(void);
  SV_Matte(const SV_Matte& m);
  virtual SV_Matte* clone(void) const;
  SV_Matte& operator=(const SV_Matte& rhs);
  ~SV_Matte(void);

  void set_ka(const float k);
  void set_kd(const float k);
  void set_cd(Texture* t_ptr);

  virtual RGBColor shade(ShadeRec& sr);
  virtual RGBColor area_light_shade(ShadeRec& sr);

private:
  void copy(const SV_Matte& other);

  SV_Lambertian* ambient_brdf;
  SV_Lambertian* diffuse_brdf;
};

inline void SV_Matte::set_ka(const float k) {
  ambient_brdf->set_kd(k);
}

inline void SV_Matte::set_kd(const float k) {
  diffuse_brdf->set_kd(k);
}

inline void SV_Matte::set_cd(Texture* t_ptr) {
  ambient_brdf->set_cd(t_ptr);
  diffuse_brdf->set_cd(t_ptr);
}

#endif
