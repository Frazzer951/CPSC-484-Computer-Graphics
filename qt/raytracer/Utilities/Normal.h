
#ifndef __NORMAL__
#define __NORMAL__

#include "Matrix.h"
#include "Vector3D.h"
#include "Point3D.h"

//=====================================
// Normal
//=====================================
//
struct Normal {
  Normal();
  Normal( double a );
  Normal( double _x, double _y, double _z );

  Normal( const Normal &n );
  Normal( const Vector3D &v );

  Normal &operator=( const Normal &n );
  Normal &operator=( const Vector3D &v );
  Normal &operator=( const Point3D &p );
  ~Normal();

  Normal          operator-() const;
  friend Vector3D operator-( const Vector3D &v, const Normal &n );

  Normal operator+( const Normal &n ) const;

  Normal &operator+=( const Normal &n );

  //    friend double operator*(const Vector3D& v, const Normal& n);
  //    friend double dot(const Normal& n, const Vector3D& v);
  double dot( const Normal &n ) const;

  friend Normal operator*( const Matrix &m, const Normal &n );

  Normal        operator*( double k ) const;
  friend Normal operator*( double k, const Normal &n );
  void          normalize();

  double x, y, z;
};

#endif
