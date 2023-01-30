#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

class Vector
{
public:
  Vector() : Vector( 0, 0, 0 ) {}
  Vector( double x, double y, double z ) : _x( x ), _y( y ), _z( z ) {}

  friend Vector operator+( const Vector & a, const Vector & b ) { return { a._x + b._x, a._y + b._y, a._z + b._z }; }
  // Vector operator+(const Vector& o) {
  //     return Vector(_x + o._x, _y + o._y, _z + o._z);
  // }

  Vector & operator+=( const Vector & o )
  {
    _x += o._x;
    _y += o._y;
    _z += o._z;
    return *this;
  }

  friend std::ostream & operator<<( std::ostream & os, const Vector & v )
  {
    return os << "Vector(" << v._x << "," << v._y << "," << v._z << ")";
  }

  static void run_tests()
  {
    Vector v;
    Vector v2( 1, 1, 2 );

    std::cout << "\n............... BEGINNING Vector.run_tests()...........\n";
    std::cout << "v is: " << v << "\n";
    std::cout << "v2 is: " << v2 << "\n";
    std::cout << "............... ENDING Vector.run_tests()..............\n\n";
  }

private:
  double _x, _y, _z;
};

#endif
