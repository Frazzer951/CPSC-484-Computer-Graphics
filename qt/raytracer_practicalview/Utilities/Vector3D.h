#ifndef __VECTOR_3D__
#define __VECTOR_3D__

#include "Matrix.h"


//=====================================
// Vector3D
//=====================================
//

struct Normal;
struct Point3D;

//----------------------------------------- class Vector3D

class Vector3D {
public:
    double	x, y, z;

public:
    Vector3D(void);
    Vector3D(double a);
    Vector3D(double _x, double _y, double _z);
    Vector3D(const Vector3D& v);
    Vector3D(const Normal& n);
    Vector3D(const Point3D& p);

    ~Vector3D (void);

    Vector3D& operator= (const Vector3D& rhs);
    Vector3D& operator= (const Normal& rhs);
    Vector3D& operator= (const Point3D& rhs);

    Vector3D operator- (void) const;

    double	length(void);
    double	len_squared(void);

    Vector3D operator* (const double a) const;
    Vector3D operator/ (const double a) const;

    Vector3D operator+ (const Vector3D& v) const;
    Vector3D& operator+= (const Vector3D& v);
    Vector3D operator- (const Vector3D& v) const;


    double dot(const Vector3D& b) const;        // dot-product    (orig. code: *)
    Vector3D cross(const Vector3D& v) const;    // cross-product  (orig. code: ^)

    void normalize(void);

    Vector3D& hat(void);
};
// inlined member functions
// ------------------------------------------------------------------------ unary minus
// this does not change the current vector
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object
inline Vector3D
Vector3D::operator- (void) const { return (Vector3D(-x, -y, -z)); }
// ---------------------------------------------------------------------  len_squared
// the square of the length
inline double
Vector3D::len_squared(void) { return (x * x + y * y + z * z); }
// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right
inline Vector3D
Vector3D::operator* (const double a) const { return (Vector3D(x * a, y * a, z * a)); }
// ----------------------------------------------------------------------- operator/
// division by a double
inline Vector3D
Vector3D::operator/ (const double a) const { return (Vector3D(x / a, y / a, z / a)); }
// ----------------------------------------------------------------------- operator+
// addition
inline Vector3D
Vector3D::operator+ (const Vector3D& v) const { return (Vector3D(x + v.x, y + v.y, z + v.z)); }
// ----------------------------------------------------------------------- operator-
// subtraction
inline Vector3D
Vector3D::operator- (const Vector3D& v) const { return (Vector3D(x - v.x, y - v.y, z - v.z)); }
// ----------------------------------------------------------------------- operator*
// dot product
//inline double
//Vector3D::operator* (const Vector3D& v) const {
inline double
Vector3D::dot(const Vector3D& v) const { return (x * v.x + y * v.y + z * v.z); }
// ----------------------------------------------------------------------- operator^
// cross product
//inline Vector3D
//Vector3D::operator^ (const Vector3D& v) const {
inline Vector3D
Vector3D::cross(const Vector3D& v) const {
    return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}
// ---------------------------------------------------------------------  operator+=
// compound addition
inline Vector3D&
Vector3D::operator+= (const Vector3D& v) {
    x += v.x; y += v.y; z += v.z;
    return (*this);
}
// inlined non-member function
// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left
Vector3D
operator* (const double a, const Vector3D& v);

inline Vector3D
operator* (const double a, const Vector3D& v) { return (Vector3D(a * v.x, a * v.y, a * v.z)); }
// non-inlined non-member function
// ----------------------------------------------------------------------- operator*
// multiplication by a matrix on the left
Vector3D
operator* (const Matrix& mat, const Vector3D& v);


#endif


