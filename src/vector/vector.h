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
  friend Vector operator-( const Vector & a, const Vector & b ) { return ( a + -b ); }

  friend Vector operator-( const Vector & a ) { return { -a.x_, -a.y_, -a.z_ }; }

  friend bool operator==( const Vector & a, const Vector & b ) { return a.x_ == b.x_ && a.y_ == b.y_ && a.z_ == b.z_; }
  friend bool operator!=( const Vector & a, const Vector & b ) { return !( a == b ); }

  Vector & operator+=( const Vector & o )
  {
    x_ += o.x_;
    y_ += o.y_;
    z_ += o.z_;
    return *this;
  }

  Vector & operator-=( const Vector & o ) { return operator+=( -o ); }

  friend std::ostream & operator<<( std::ostream & os, const Vector & v )
  {
    return os << "Vector(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
  }

  // dot prod
  double dot( const Vector & a, const Vector & b ) { return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_; }

  // cross prod

  // multiply by scalar
  friend Vector operator*( double k, const Vector & a ) { return { k * a.x_, k * a.y_, k * a.z_ }; }

  // divide by scalar

  // norm

  // magnitude
  double magnitude() { return sqrt( dot( *this, *this ) ); }

  static void run_tests()
  {
    Vector v;
    Vector v2( 1, 1, 2 );


    std::cout << "\n............... BEGINNING Vector.run_tests()...........\n";
    std::cout << "v is: \t\t" << v << "\n";
    std::cout << "v2 is: \t\t" << v2 << "\n";
    std::cout << "-v2 is: \t" << -v2 << "\n";

    Vector v3 = v + v2;
    std::cout << "v3 is: \t\t" << v3 << "\n";

    v3 += v2;
    std::cout << "v3 += v2 is: \t" << v3 << "\n";

    Vector v4 = v3 - v2;
    std::cout << v3 << " - " << v2 << " is: \t" << v4 << "\n";

    v4 -= v2;
    std::cout << "v4 -= v2 is: \t" << v4 << "\n";

    Vector vtest = v3;
    vtest += v2;
    vtest -= v2;
    assert( v3 == vtest );
    assert( v3 != v4 );

    std::cout << "............... ENDING Vector.run_tests()..............\n\n";
  }

private:
  double x_, y_, z_;
};

#endif
