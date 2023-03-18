//#include "LightProbeMap.h"

//LightProbeMap::LightProbeMap(void)
//:  Mapping(), map_type(light_proble) {
//}

//// ---------------------------------------------------------------- copy constructor

//LightProbeMap::LightProbeMap(const LightProbeMap& sm)
//: Mapping(sm) { }

//// ---------------------------------------------------------------- assignment operator

//LightProbeMap& LightProbeMap::operator= (const LightProbeMap& rhs) {
//  if (this == &rhs) { return (*this); }
//  return (*this);
//}

//// ---------------------------------------------------------------- destructor

//LightProbeMap::~LightProbeMap (void) {}

//// ---------------------------------------------------------------- clone

//LightProbeMap* LightProbeMap::clone(void) const { return (new LightProbeMap(*this)); }

//void LightProbeMap::get_texel_coordinates(const Point3D& hit_point,
//       int hres, int vres,  int& row, int& column) const {

//     float x = hit_point.x; float y = hit_point.y; float z = hit_point.z;

//     float d = sqrt(x * x + y * y);
//     float sin_beta = y / d;
//     float cos_beta = x / d;
//     float alpha;

//     if (map_type == light_probe)       // the default
//          alpha = acos(z);

//     if (map_type == panoramic)
//          alpha = acos(-z);

//     float r = alpha * invPI;
//     float u = (1.0 + r * cos_beta) * 0.5;
//     float v = (1.0 + r * sin_beta) * 0.5;
//     column = (int) ((hres - 1) * u);
//     row = (int) ((vres - 1) * v);
//}
