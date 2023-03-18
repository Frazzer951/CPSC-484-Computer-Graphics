#ifndef __RECTANGULARMAP__
#define __RECTANGULARMAP__

#include "Mapping.h"

class RectangularMap : public Mapping {
public:
  virtual void get_pixel_coordinates( const Point3D &local_hit_point, int hres, int vres, int &row, int &column ) const = 0;
  virtual void LightProbeMap::get_texel_coordinates( const Point3D &hit_point, int hres, int vres, int &row,
                                                     int &column ) const                                                = 0;

private:
};

#endif
