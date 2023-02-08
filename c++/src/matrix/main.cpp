//============================================================
// file: main.cpp
//============================================================
#include <iostream>
#include <cstring>
#include <string>
#include <initializer_list>
#include <cassert>

// MATRIX and VECTOR classes assignment
#include "vector3dT.h"
#include "matrix3dT.h"

void test_matrices_and_vectors()
{
  std::cout << "\n====================  TESTING MATRICES and VECTORS  ========================\n";
  vector3D  p( "p", 2, { 1, 2 } );
  matrix3dD m( "m", 2, { 1, 2, 3, 4 } );
  std::cout << p << std::endl;
  std::cout << m << std::endl;

  std::cout << "...test p * m == m * p \n";
  assert( p * m == m * p );
  std::cout << "...test p * m == m * p passed \n";

  vector3D  q( "q", 3, { 1, 2, 3 } );
  matrix3dD n( "n", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
  std::cout << ( q ) << std::endl;
  std::cout << ( n ) << std::endl;

  std::cout << "...test q * n == n * q \n";
  assert( q * n == n * q );
  std::cout << "...test q * n == n * q passed \n";


  std::cout << "...test_matrices_and_vectors assertions passed\n";
  std::cout << "====================  FINISHED TESTING MATRICES and VECTORS  ========================\n";
}

void test_matrices()
{
  std::cout << "\n====================  TESTING MATRICES  ========================\n";
  matrix3dD m( "m", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
  matrix3dD mT( "mT", 3, { 1, 4, 7, 2, 5, 8, 3, 6, 9 } );


  std::cout << m << std::endl;
  std::cout << mT << std::endl;

  //=========================================================
  //=========================================================

  std::cout << "...test matrices transpose \n";
  assert( m.transpose() == mT );
  std::cout << "...test matrices transpose passed\n";

  //=========================================================
  //=========================================================
  std::cout << "...test matrices copy constructor \n";
  matrix3dD m2( m );
  assert( m2 == m );
  std::cout << "...test matrices copy constructor passed\n";
  //=========================================================
  //=========================================================

  std::cout << "...test matrices assignment operator \n";
  matrix3dD m3( "m3", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
  m3 = m;
  assert( m3 == m );
  std::cout << "...test matrices assignment operator passed\n";
  //=========================================================
  //=========================================================

  std::cout << "...test matrices equality operator \n";
  assert( m == m );
  assert( m == m2 );
  assert( m == m3 );
  std::cout << "...test matrices equality operator passed\n";
  //=========================================================
  //=========================================================

  std::cout << "...test matrices inequality operator \n";
  matrix3dD m4( "m4", 3, { 0, 1, 2, 3, 5, 7, 0, 25, 63 } );
  assert( m != m4 );
  std::cout << "...test matrices inequality operator passed\n";
  //=========================================================
  //=========================================================

  std::cout << "...test matrices sign operators \n";

  //=========================================================
  std::cout << "...testing matrix addition and subtraction\n";
  matrix3dD m5( "m5", 3, { 2, 4, 6, 8, 10, 12, 14, 16, 18 } );
  assert( m + m == m5 );
  assert( m5 - m == m );
  assert( m5 - m5 == matrix3dD( "m5", 3, { 0, 0, 0, 0, 0, 0, 0, 0, 0 } ) );
  assert( matrix3dD( "a", 3, { 1, 3, -4, 4, 8, 5, 9, 8, 6 } ) + matrix3dD( "b", 3, { 5, 9, -5, 2, -6, 4, 4, 6, 7 } )
          == matrix3dD( "c", 3, { 6, 12, -9, 6, 2, 9, 13, 14, 13 } ) );

  matrix3dD addeq( "+=", 3, { 1, 3, -4, 8, 5, 7, 9, 8, 6 } );
  assert( ( addeq += matrix3dD( "b", 3, { 2, 9, -5, 2, -6, -6, 2, 4, 6 } ) )
          == matrix3dD( "c", 3, { 3, 12, -9, 10, -1, 1, 11, 12, 12 } ) );

  matrix3dD subeq( "-=", 3, { 1, 3, -4, 1, 8, 5, 1, 1, 1 } );
  assert( ( subeq -= matrix3dD( "b", 3, { 1, 3, -4, 1, 8, 5, 1, 1, 1 } ) ) == matrix3dD::zero( 3 ) );
  std::cout << "...testing matrix addition and subtraction passed\n";
  //=========================================================
  //=========================================================
  std::cout << "...testing matrix scalar multiplication\n";
  assert( m * 2 == m5 );
  assert( 2 * m == m5 );
  assert( m * 0 == matrix3dD::zero( 3 ) );
  assert( 0 * m == matrix3dD::zero( 3 ) );
  assert( matrix3dD( "a", 3, { 1, 1, 5, -2, 7, 3, 1, 1, 1 } ) * 3
          == matrix3dD( "result", 3, { 3, 3, 15, -6, 21, 9, 3, 3, 3 } ) );

  matrix3dD m6( "m6", 3, { 1, 5, -2, 1, 7, 3, 3, 3, 3 } );
  assert( ( m6 *= 3 ) == matrix3dD( "result", 3, { 3, 15, -6, 3, 21, 9, 9, 9, 9 } ) );

  std::cout << "...testing matrix scalar multiplication passed\n";
  //=========================================================
  //=========================================================
  std::cout << "...testing matrix scalar division\n";
  m6 = matrix3dD( "m6", 3, { 3, 15, -6, 12, 21, 9, 9, 9, 9 } );
  assert( m5 / 2 == m );
  assert( m6 / 3 == matrix3dD( "result", 3, { 1, 5, -2, 4, 7, 3, 3, 3, 3 } ) );
  assert( ( m6 /= 3 ) == matrix3dD( "result", 3, { 1, 5, -2, 4, 7, 3, 3, 3, 3 } ) );

  std::cout << "...testing matrix scalar division passed\n";
  //=========================================================
  //=========================================================
  std::cout << "...testing matrix scalar addition and subtraction\n";
  assert( m + 2 == matrix3dD( "m", 3, { 3, 4, 5, 6, 7, 8, 9, 10, 11 } ) );
  assert( 2 + m == matrix3dD( "m", 3, { 3, 4, 5, 6, 7, 8, 9, 10, 11 } ) );
  assert( m - 2 == matrix3dD( "m", 3, { -1, 0, 1, 2, 3, 4, 5, 6, 7 } ) );
  assert( 2 - m == matrix3dD( "m", 3, { 1, 0, -1, -2, -3, -4, -5, -6, -7 } ) );
  assert( ( m += 2 ) == matrix3dD( "m", 3, { 3, 4, 5, 6, 7, 8, 9, 10, 11 } ) );
  assert( ( m -= 2 ) == matrix3dD( "m", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } ) );


  std::cout << "...testing matrix multiplication\n";
  matrix3dD m7( "m7", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );

  assert( m * m7 == matrix3dD( "m", 3, { 30, 36, 42, 66, 81, 96, 102, 126, 150 } ) );
  assert( m7 * m == matrix3dD( "m", 3, { 30, 36, 42, 66, 81, 96, 102, 126, 150 } ) );

  std::cout << "...testing matrix multiplication passed\n";

  //=========================================================
  //=========================================================
  std::cout << "...testing matrix sign operators passed\n";

  //=========================================================
  //=========================================================
  std::cout << "...testing matrix unary minus\n";
  matrix3dD m8( "m8", 3, { -1, -2, -3, -4, -5, -6, -7, -8, -9 } );
  assert( -m == m8 );

  std::cout << "...testing matrix unary minus passed\n";


  std::cout << "...testing matrix transpose, minor, cofactor, determinant, adjoint, and inverse\n";

  matrix3dD c( "c", 3, { -1, -2, 2, 2, 1, 1, 3, 4, 5 } );

  std::cout << c << std::endl;
  std::cout << "...asserting transpose" << std::endl;
  assert( c.transpose().transpose() == c );
  std::cout << "...asserting transpose passed" << std::endl;

  std::cout << "...asserting minors" << std::endl;
  assert( c.minors() == matrix3dD( "c", 3, { 1, 7, 5, -18, -11, 2, -4, -5, 3 } ) );
  std::cout << "...asserting minors passed" << std::endl;

  std::cout << "...asserting cofactors" << std::endl;
  assert( c.cofactor() == matrix3dD( "c", 3, { 1, -7, 5, 18, -11, -2, -4, 5, 3 } ) );
  std::cout << "...asserting cofactors passed" << std::endl;

  std::cout << "...asserting determinant" << std::endl;
  assert( c.determinant() == 23 );
  std::cout << "...asserting determinant passed" << std::endl;

  std::cout << "...asserting adjoint (TRANSPOSE OF COFACTOR MATRIX)" << std::endl;
  assert( c.adjoint() == matrix3dD( "c", 3, { 1, 18, -4, -7, -11, 5, 5, -2, 3 } ) );
  std::cout << "...asserting adjoint passed" << std::endl;

  std::cout << "...asserting inverse" << std::endl;
  assert( c.inverse()
          == matrix3dD(
              "c", 3,
              { 1.0 / 23, 18.0 / 23, -4.0 / 23, -7.0 / 23, -11.0 / 23, 5.0 / 23, 5.0 / 23, -2.0 / 23, 3.0 / 23 } ) );
  std::cout << "...asserting inverse passed" << std::endl;

  std::cout << "...asserting identity" << std::endl;
  std::cout << matrix3dD::identity( 3 ) << std::endl;
  assert( c.identity( 3 ) == matrix3dD( "c", 3, { 1, 0, 0, 0, 1, 0, 0, 0, 1 } ) );
  std::cout << "...asserting identity passed" << std::endl;

  std::cout << "...testing matrix transpose, minor, cofactor, determinant, adjoint, and inverse passed\n";

  //=========================================================
  //=========================================================


  std::cout << "==========================================================================\n";
  std::cout << "==========================  TESTING PASSED  =============================\n";
  std::cout << "==========================================================================\n";
  std::cout << "====================  FINISHED TESTING MATRICES  ========================\n";
}

void test_openGL()
{
  std::cout << "\n==========================================================================\n";
  std::cout << "====================  TESTING OPENGL FUNCTIONS  =========================\n";
  std::cout << "==========================================================================\n";

  std::cout << "...testing opengl_matrix\n";
  matrix3dD m( "m", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
  std::cout << m << std::endl;
  std::string testStr      = "1 4 7 0 2 5 8 0 3 6 9 0 0 0 0 1";
  double *    openGLMatrix = m.opengl_memory( 3, 3 );

  std::string colMajor = "";
  for( int i = 0; i < 15; i++ )
  {
    colMajor += std::to_string( int( openGLMatrix[i] ) ) + " ";
  }
  colMajor += std::to_string( int( openGLMatrix[15] ) );

  std::cout << testStr << std::endl;
  std::cout << colMajor << std::endl;

  assert( testStr == colMajor );
  std::cout << std::endl;
  std::cout << "...testing opengl_matrix passed\n";

  std::cout << "==========================================================================\n";
  std::cout << "==========================  TESTING PASSED  =============================\n";
  std::cout << "==========================================================================\n";
  std::cout << "====================  FINISHED TESTING OPENGL  ==========================\n";
}


int main( int argc, const char * argv[] )
{
  vector3D::run_tests();
  test_matrices_and_vectors();
  test_matrices();
  test_openGL();

  return 0;
}


/*
====================  TESTING VECTORS  ========================
u.name_ is: u
<u,   1   2   4   0>
<u,   1   2   4   0>
<v,   8  16  32   0>
<i,   1   0   0   0>
<j,   0   1   0   0>
<k,   0   0   1   0>
j + k is: <j+k,   0   1   1   0>
<3.000000i+4.000000j-2.000000k,   3   4  -2   0>
*** asserting u == u and u != v
*** asserting u + v == v + u   and  u - v == -(v - u)    and   -(-u) == u
*** 3.0 + u == u + 3.0   and   3.0 * u == u * 3.0
*** asserting u - 3.- == -(3.0 - u)
*** asserting 5.0 * u == u * 5.0
*** asserting u + vector3D::zero() == u
*** asserting i.dot(j) == j.dot(k) == k.dot(i) == 0
*** asserting i.cross(j) == k   and  j.cross(k) == i   and   k.cross(i) == j
*** asserting u.cross(v) == -v.cross(u)
i.angle(j) is: 1.57
pi/2 is: 1.57
*** asserting i.angle(j) == j.angle(k) == k.angle(i) == M_PI/2
<u,   1   2   4   0>
<0.218218u, 0.218 0.436 0.873   0>
length of uhat.mag() is... 1
*** asserting u.hat.mag() - 1.0 < 1.0e-10
...test vectors assertions passed
====================  FINISHED testing vectors  ========================


====================  TESTING MATRICES and VECTORS  ========================
<p,   1   2   0>
<'m', <col0,   1   3   0   0><col1,   2   4   0   0><col2,   0   0   0   0>> OR by rows...
  1   2   0
  3   4   0
  0   0   0
>
...test p * m == m * p
...test p * m == m * p passed
<q,   1   2   3   0>
<'n', <col0,   1   4   7   0><col1,   2   5   8   0><col2,   3   6   9   0>> OR by rows...
  1   2   3
  4   5   6
  7   8   9
>
...test q * n == n * q
...test q * n == n * q passed
...test_matrices_and_vectors assertions passed
====================  FINISHED TESTING MATRICES and VECTORS  ========================

====================  TESTING MATRICES  ========================
<'m', <col0,   1   4   7   0><col1,   2   5   8   0><col2,   3   6   9   0>> OR by rows...
  1   2   3
  4   5   6
  7   8   9
>
<'mT', <col0,   1   2   3   0><col1,   4   5   6   0><col2,   7   8   9   0>> OR by rows...
  1   4   7
  2   5   8
  3   6   9
>
...test matrices transpose
...test matrices transpose passed
...test matrices copy constructor
...test matrices copy constructor passed
...test matrices assignment operator
...test matrices assignment operator passed
...test matrices equality operator
...test matrices equality operator passed
...test matrices inequality operator
...test matrices inequality operator passed
...test matrices sign operators
...testing matrix addition and subtraction
...testing matrix addition and subtraction passed
...testing matrix scalar multiplication
...testing matrix scalar multiplication passed
...testing matrix scalar division
...testing matrix scalar division passed
...testing matrix scalar addition and subtraction
...testing matrix multiplication
...testing matrix multiplication passed
...testing matrix sign operators passed
...testing matrix unary minus
...testing matrix unary minus passed
...testing matrix transpose, minor, cofactor, determinant, adjoint, and inverse
<'c', <col0,  -1   2   3   0><col1,  -2   1   4   0><col2,   2   1   5   0>> OR by rows...
 -1  -2   2
  2   1   1
  3   4   5
>
...asserting transpose
...asserting transpose passed
...asserting minors
...asserting minors passed
...asserting cofactors
...asserting cofactors passed
...asserting determinant
...asserting determinant passed
...asserting adjoint (TRANSPOSE OF COFACTOR MATRIX)
...asserting adjoint passed
...asserting inverse
...asserting inverse passed
...asserting identity
<'I3', <col0,   1   0   0   0><col1,   0   1   0   0><col2,   0   0   1   0>> OR by rows...
  1   0   0
  0   1   0
  0   0   1
>
...asserting identity passed
...testing matrix transpose, minor, cofactor, determinant, adjoint, and inverse passed
==========================================================================
==========================  TESTING PASSED  =============================
==========================================================================
====================  FINISHED TESTING MATRICES  ========================

==========================================================================
====================  TESTING OPENGL FUNCTIONS  =========================
==========================================================================
...testing opengl_matrix
<'m', <col0,   1   4   7   0><col1,   2   5   8   0><col2,   3   6   9   0>> OR by rows...
  1   2   3
  4   5   6
  7   8   9
>
1 4 7 0 2 5 8 0 3 6 9 0 0 0 0 1
1 4 7 0 2 5 8 0 3 6 9 0 0 0 0 1

...testing opengl_matrix passed
==========================================================================
==========================  TESTING PASSED  =============================
==========================================================================
====================  FINISHED TESTING OPENGL  ==========================
*/
