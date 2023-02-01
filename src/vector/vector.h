#ifndef __VECTOR_H__
#define __VECTOR_H__

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
  double mag() const { return sqrt( dot( *this, *this ) ); }

  // cross product
  static Vector cross( const Vector & a, const Vector & b )
  {
    double const x = ( a.y_ * b.z_ ) - ( a.z_ * b.y_ );
    double const y = ( a.z_ * b.x_ ) - ( a.x_ * b.z_ );
    double const z = ( a.x_ * b.y_ ) - ( a.y_ * b.x_ );
    return { x, y, z };
  }

  // multiply by a scalar
  friend Vector operator*( const Vector & a, double k ) { return { k * a.x_, k * a.y_, k * a.z_ }; }
  friend Vector operator*( double k, const Vector & a ) { return { a * k }; }

  // divide by a scalar
  friend Vector operator/( const Vector & a, double k ) { return { a.x_ / k, a.y_ / k, a.z_ / k }; }

  // norm
  Vector norm() { return *this / this->mag(); }

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
    std::cout << v << " + " << v2 << " is: " << v3 << "\n";

    Vector const v4 = v3 - v2;
    std::cout << v3 << " - " << v2 << " is: " << v4 << "\n";

    v3 += v2;
    std::cout << "v3 after incrementing by: " << v2 << " is: " << v3 << "\n";

    v3 -= v2;
    std::cout << "v3 after decrementing by: " << v2 << " is: " << v3 << "\n";

    std::cout << "-v2 is: " << -v2 << "\n";

    assert( Vector( 1, 1, 1 ) == Vector( 1, 1, 1 ) );
    assert( Vector( 1, 1, 1 ) != Vector( 0, 0, 0 ) );

    Vector const v5( 1, 2, 3 );
    Vector       v6( 1, 5, 7 );
    std::cout << v5 << " * " << v6 << " is: " << Vector::dot( v5, v6 ) << "\n";
    std::cout << v5 << " X " << v6 << " is: " << Vector::cross( v5, v6 ) << "\n";

    std::cout << "Magnitude of " << v6 << " is: " << v6.mag() << "\n";

    std::cout << v5 << " * 5 is: " << v5 * 5 << "\n";
    std::cout << "5 * " << v5 << " is: " << 5 * v5 << "\n";

    Vector const v7( 2, 2, 2 );
    std::cout << v7 << " / 2 is: " << v7 / 2 << "\n";

    Vector v8 = v6.norm();
    std::cout << "Normal of " << v6 << " is: " << v8 << "\n";
    std::cout << "Magnitude of " << v8 << " is: " << v8.mag() << "\n";

    std::cout << "............... ENDING Vector.run_tests()..............\n\n";
  }

private:
  double x_, y_, z_;
};

#endif
