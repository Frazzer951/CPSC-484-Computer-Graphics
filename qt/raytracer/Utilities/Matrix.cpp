// This file contains the definition of the class Matrix

#include "Matrix.h"

// ----------------------------------------------------------------------- default constructor
// a default matrix is an identity matrix

Matrix::Matrix( void ) {
  for ( int x = 0; x < 4; x++ ) {
    for ( int y = 0; y < 4; y++ ) { m[x][y] = x == y ? 1.0 : 0.0; }
  }
}

Matrix::Matrix( const Matrix &other ) : Matrix() { copy( other ); }

Matrix &Matrix::operator=( const Matrix &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

Matrix::~Matrix( void ) {}

void Matrix::copy( const Matrix &other ) {
  for ( int x = 0; x < 4; x++ ) {
    for ( int y = 0; y < 4; ++y ) { m[x][y] = other.m[x][y]; }
  }
}

// ----------------------------------------------------------------------- operator*
// multiplication of two matrices

Matrix Matrix::operator*( const Matrix &other ) const {
  Matrix product;

  for ( int y = 0; y < 4; ++y ) {
    for ( int x = 0; x < 4; ++x ) {
      double sum = 0.0;
      for ( int j = 0; j < 4; ++j ) { sum += m[x][j] * other.m[j][y]; }
      product.m[x][y] = sum;
    }
  }
  return ( product );
}

// ----------------------------------------------------------------------- operator/
// division by a scalar

Matrix Matrix::operator/( const double d ) {
  for ( int x = 0; x < 4; ++x ) {
    for ( int y = 0; y < 4; ++y ) { m[x][y] = m[x][y] / d; }
  }
  return ( *this );
}

// ----------------------------------------------------------------------- set_identity
// set matrix to the identity matrix

void Matrix::set_identity( void ) {
  for ( int x = 0; x < 4; ++x ) {
    for ( int y = 0; y < 4; ++y ) { m[x][y] = x == y ? 1.0 : 0.0; }
  }
}
