//============================================================
// file: main.cpp
//============================================================
#include <iostream>
#include <cstring>
#include <initializer_list>
#include <cassert>

// MATRIX and VECTOR classes assignment
#include "vector3dT.h"
#include "matrix3dT.h"

void test_matrices_and_vectors()
{
  std::cout << "\n====================  TESTING MATRICES and VECTORS  ========================\n";
  vector3D const  p( "p", 2, { 1, 2 } );
  matrix3dD const m( "m", 2, { 1, 2, 3, 4 } );
  std::cout << p << std::endl;
  std::cout << m << std::endl;
  assert( p * m == m * p );

  vector3D const  q( "q", 3, { 1, 2, 3 } );
  matrix3dD const n( "n", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
  std::cout << ( q ) << std::endl;
  std::cout << ( n ) << std::endl;
  assert( q * n == n * q );


  std::cout << "...test_matrices_and_vectors assertions passed\n";
  std::cout << "====================  FINISHED TESTING MATRICES and VECTORS  ========================\n";
}

void test_matrices()
{
  std::cout << "\n====================  TESTING MATRICES  ========================\n";
  matrix3dD       m( "m", 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
  matrix3dD const mT( "mT", 3, { 1, 4, 7, 2, 5, 8, 3, 6, 9 } );


  std::cout << m << std::endl;

  //=========================================================
  //=========================================================

  std::cout << "...test matrices transpose \n";
  assert( m.transpose() == mT );
  std::cout << "...test matrices transpose passed\n";

  //=========================================================
  //=========================================================
  std::cout << "...test matrices copy constructor \n";
  matrix3dD const m2( m );
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
  matrix3dD const m4( "m4", 3, { 0, 1, 2, 3, 5, 7, 0, 25, 63 } );
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
  matrix3dD const m8( "m8", 3, { -1, -2, -3, -4, -5, -6, -7, -8, -9 } );
  assert( -m == m8 );

  std::cout << "...testing matrix unary minus passed\n";


  std::cout << "...testing matrix transpose, minor, cofactor, determinant, adjoint, and inverse\n";

  matrix3dD const c( "c", 3, { -1, -2, 2, 2, 1, 1, 3, 4, 5 } );

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


  std::cout << "...testing matrix transpose, minor, cofactor, determinant, adjoint, and inverse passed\n";

  std::cout << "==========================================================================\n";
  std::cout << "==========================  TESTING PASSED  =============================\n";
  std::cout << "==========================================================================\n";
  std::cout << "====================  FINISHED TESTING MATRICES  ========================\n";
}


int main( int /*argc*/, const char * /*argv*/[] )
{
  vector3D::run_tests();
  test_matrices();
  test_matrices_and_vectors();

  return 0;
}
