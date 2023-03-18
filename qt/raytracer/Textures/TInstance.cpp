//#include "TInstance.h"
//#include "Utilities/Matrix.h"
//#include "Utilities/RGBColor.h"

//void TInstance::scale(const float sx, const float sy, const float sz) {
//     Matrix inv_scaling_matrix;      // temporary inverse scaling matrix

//     inv_scaling_matrix.m [0][0] = 1.0 / sx;
//     inv_scaling_matrix.m [1][1] = 1.0 / sy;
//     inv_scaling_matrix.m [2][2] = 1.0 / sz;

//     inv_matrix = inv_matrix * inv_scaling_matrix;
//}

//RGBColor TInstance::get_color(const ShadeRec& sr) const {
//     ShadeRec local_sr(sr);
//     local_sr.local_hit_point *= inv_matrix;

//     return (texture_ptr->get_color(local_sr));
//}
