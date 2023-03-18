//#include "FresnelReflector.h"

//FresnelReflector::FresnelReflector(void)
//: BRDF(),
//  kd(1.0),
//  cd(black)
//{ }

//FresnelReflector::FresnelReflector(const FresnelReflector& other)
//: FresnelReflector() { copy(other); }

//FresnelReflector& FresnelReflector::operator= (const FresnelReflector& other) {
//    if (this != &other) { copy(other); }
//    return (*this);
//}

//void FresnelReflector::copy(const FresnelReflector& other) {
//    BRDF::operator=(other);

//    kd = other.kd;
//    cd = other.cd;
//}

//FresnelReflector::~FresnelReflector(void);

//FresnelReflector* FresnelReflector::clone(void) const;

//float FresnelReflector::fresnel(const ShadeRec& sr) const {
//    Normal normal(sr.normal);
//    float ndotd = -normal * sr.ray.d;
//    float eta;

//    if (ndotd < 0.0) {          // ray hits inside surface
//         normal = -normal;
//         eta = eta_out / eta_in;
//    }
//    else
//         eta = eta_in / eta_out;

//    float cos_theta_i = -normal * sr.ray.d;
//    float temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
//    float cos_theta_t = sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) /
//             (eta * eta));
//    float r_parallel = (eta * cos_theta_i - cos_theta_t) /
//              (eta * cos_theta_i + cos_theta_t);
//    float r_perpendicular = (cos_theta_i - eta * cos_theta_t) /
//              (cos_theta_i + eta * cos_theta_t);
//    float kr = 0.5 * (r_parallel * r_parallel + r_perpendicular
//             * r_perpendicular);

//    return (kr);
//}

//#endif
