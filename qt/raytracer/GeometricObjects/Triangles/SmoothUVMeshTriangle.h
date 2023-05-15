#ifndef __SMOOTHUVMESHTRIANGLE__
#define __SMOOTHUVMESHTRIANGLE__

#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle : public SmoothMeshTriangle {
public:
  SmoothUVMeshTriangle( void );
  SmoothUVMeshTriangle( Mesh *_meshPtr, const int i0, const int i1, const int i2 );

  SmoothUVMeshTriangle( const SmoothUVMeshTriangle &fmt );

  virtual SmoothUVMeshTriangle *clone( void ) const;
  SmoothUVMeshTriangle         &operator=( const SmoothUVMeshTriangle &rhs );

  virtual ~SmoothUVMeshTriangle( void );

  virtual bool hit( const Ray &ray, double &tmin, ShadeRec &sr ) const;
  //    virtual bool shadow_hit(const Ray& ray, double& tmin) const;
  bool         shadow_hit( const Ray &ray, double &tmin, ShadeRec &sr ) const;
};

#endif
