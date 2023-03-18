#ifndef __LIGHTPROBEMAP__
#define __LIGHTPROBEMAP__

#include "Mapping.h"
#include "Utilities/Constants.h"

class LightProbeMap : public Mapping {
public:
  LightProbeMap( void );
  LightProbeMap( const LightProbeMap &sm );

  LightProbeMap &operator=( const LightProbeMap &rhs );

  virtual LightProbeMap *clone( void ) const;
  ~LightProbeMap( void );

  //    virtual void get_pixel_coordinates (const Point3D& local_hit_point,
  //                                        int hres, int vres, int& row, int& column) const = 0;
  virtual void LightProbeMap::get_texel_coordinates( const Point3D &hit_point, int hres, int vres, int &row,
                                                     int &column ) const = 0;

private:
  int map_type;
};

#endif
