#include <math.h>
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"

class Vector;
class Point;

Normal::Normal() : x( 0.0 ), y( 0.0 ), z( 0.0 ) {}

Normal::Normal( double a ) : x( a ), y( a ), z( a ) {}

Normal::Normal( double _x, double _y, double _z ) : x( _x ), y( _y ), z( _z ) {}

Normal::Normal( const Normal &n ) : x( n.x ), y( n.y ), z( n.z ) {}

Normal::Normal( const Vector3D &v ) : x( v.x ), y( v.y ), z( v.z ) {}

Normal::~Normal() {}

Normal Normal::operator-() const { return Normal( -x, -y, -z ); }

Vector3D operator-( const Vector3D &v, const Normal &n ) { return Vector3D( v.x - n.x, v.y - n.y, v.z - n.z ); }

Normal Normal::operator+( const Normal &n ) const { return Normal( x + n.x, y + n.y, z + n.z ); }

Normal &Normal::operator+=( const Normal &n ) {
  x += n.x;
  y += n.y;
  z += n.z;
  return *this;
}

//double dot(const Normal& n, const Vector3D& v)   { return n.x * v.x  + n.y * v.y  + n.z * v.z; }
double Normal::dot( const Normal &n ) const { return x * n.x + y * n.y + z * n.z; }

Normal Normal::operator*( double k ) const { return Normal( k * x, k * y, k * z ); }

Normal operator*( double k, const Normal &n ) { return n * k; }

//// ----------------------------------------------------------- operator=
//// assignment operator

Normal &Normal::operator=( const Normal &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void Normal::copy( const Normal &other ) {
  x = other.x;
  y = other.y;
  z = other.z;
}

// ------------------------------------------------------------ operator=
// assignment of a vector to a normal

Normal &Normal::operator=( const Vector3D &rhs ) {
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;
  return ( *this );
}

// ------------------------------------------------------------ operator=
// assignment of a point to a normal

Normal &Normal::operator=( const Point3D &rhs ) {
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;
  return ( *this );
}

//// ------------------------------------------------------------ normalize

void Normal::normalize() {
  double length  = sqrt( x * x + y * y + z * z );
  x             /= length;
  y             /= length;
  z             /= length;
}

// non-member function definition

// ---------------------------------------------------------- operator*
// multiplication by a matrix on the left

// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix

Normal operator*( const Matrix &mat, const Normal &n ) {
  return ( Normal( mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
                   mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
                   mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z ) );
}
