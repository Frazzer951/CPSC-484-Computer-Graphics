#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>
#include <cmath>

class Vector
{
public:
  Vector() : Vector( 0, 0, 0 ) {}
  Vector( double x, double y, double z ) : x_( x ), y_( y ), z_( z ) {}

  friend Vector operator+( const Vector & a, const Vector & b ) { return { a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_ }; }
  friend Vector operator-( const Vector & a, const Vector & b ) { return a + -b; }

  friend Vector operator-( const Vector & a ) { return { -a.x_, -a.y_, -a.z_ }; }

  Vector & operator+=( const Vector & o )
  {
    x_ += o.x_;
    y_ += o.y_;
    z_ += o.z_;
    return *this;
  }
  Vector & operator-=( const Vector & o ) { return operator+=( -o ); }

  friend bool operator==( const Vector & a, const Vector & b ) { return a.x_ == b.x_ && a.y_ == b.y_ && a.z_ == b.z_; }
  friend bool operator!=( const Vector & a, const Vector & b ) { return !( a == b ); }

  // dot product
  static double dot( const Vector & a, const Vector & b ) { return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_; }

  // magnitude
  double mag()
  {
    const Vector & a = *this;
    return sqrt( dot( a, a ) );
  }

  // multiply by a scalar
  friend Vector operator*( const Vector & a, double k ) { return { k * a.x_, k * a.y_, k * a.z_ }; }
  // divide by a scalar

  // cross product

  // norm

  friend std::ostream & operator<<( std::ostream & os, const Vector & v )
  {
    return os << "Vector(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
  }


  static void run_tests()
  {
    Vector const v;
    Vector const v2( 1, 1, 2 );

    std::cout << "\n............... BEGINNING Vector.run_tests()...........\n";
    std::cout << "v is: " << v << "\n";
    std::cout << "v2 is: " << v2 << "\n";

    Vector v3 = v + v2;
    std::cout << "v3 is: " << v3 << "\n";

    v3 += v2;
    std::cout << "v3 after incrementing by: " << v2 << " is: " << v3 << "\n";

    v3 -= v2;
    std::cout << "v3 after decrementing by: " << v2 << " is: " << v3 << "\n";

    Vector vtest = v3;
    vtest += v2;
    vtest -= v2;
    assert( v3 == vtest );

    Vector const v4 = -v2;
    std::cout << "-v2 is: " << -v2 << "\n";

    Vector const v5 = v4 - v2;
    std::cout << v4 << " - " << v2 << " is: " << v5 << "\n";

    std::cout << "............... ENDING Vector.run_tests()..............\n\n";
  }

private:
  double x_, y_, z_;
};

#endif
