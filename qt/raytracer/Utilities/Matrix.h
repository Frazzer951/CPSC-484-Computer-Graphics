#ifndef __MATRIX__
#define __MATRIX__

// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

//=====================================
// Matrix
//=====================================
//
struct Matrix {
  Matrix( void );

  Matrix( const Matrix &mat );
  Matrix &operator=( const Matrix &rhs );

  ~Matrix();

  Matrix operator*( const Matrix &mat ) const;
  Matrix operator/( const double d );

  void set_identity();

  double m[4][4];
};

#endif
