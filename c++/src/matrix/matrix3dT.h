//============================================================
// FILE: matrix_3dT.h
//============================================================
#ifndef __matrix_3d__
#define __matrix_3d__

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include "vector3dT.h"

template<typename T>
class matrix3d;
template<typename T>
std::ostream &           operator<<( std::ostream & os, const matrix3d<T> & m );
typedef matrix3d<double> matrix3dD;
typedef matrix3d<float>  matrix3dF;
typedef matrix3d<int>    matrix3dI;
typedef matrix3d<long>   matrix3dL;

double epsilon = 1e-10;

template<typename T>
class matrix3d
{
public:
  matrix3d();
  matrix3d( const std::string & name, int dims );
  matrix3d( const std::string & name, int dims, const std::initializer_list<vector3d<T>> & li );
  matrix3d( const std::string & name, int dims, const std::initializer_list<T> & li );
  //=======================================================================
  matrix3d<T> & operator=( T array[9] );
  matrix3d<T> & operator=( T k );
  //=======================================================================
  // indexing ops...
  vector3d<T>   operator[]( int i ) const;
  vector3d<T> & operator[]( int i );

  T   operator()( int row, int col ) const;
  T & operator()( int row, int col );

  T * opengl_memory( int row, int col );
  //=======================================================================
  void                name( const std::string & name );
  const std::string & name() const;

  void dims( const int & dims );
  int  dims() const;
  //============================ LINEAR ALGEBRA =========================
  matrix3d<T> & operator+=( T k );
  matrix3d<T> & operator-=( T k );
  matrix3d<T> & operator*=( T k );
  matrix3d<T> & operator/=( T k );
  //=======================================================================
  matrix3d<T> & operator+=( const matrix3d<T> & b );
  matrix3d<T> & operator-=( const matrix3d<T> & b );
  //=======================================================================
  matrix3d<T> operator-();
  matrix3d<T> operator+( const matrix3d<T> & b );
  matrix3d<T> operator-( const matrix3d<T> & b );
  //=======================================================================
  friend matrix3d operator+( const matrix3d & a, T k )
  {
    return matrix3d( std::to_string( k ) + "+" + a.name(), 3, { a[0] + k, a[1] + k, a[2] + k } );
  }
  friend matrix3d operator+( T k, const matrix3d & a ) { return a + k; }
  friend matrix3d operator-( const matrix3d & a, T k ) { return a + -k; }
  friend matrix3d operator-( T k, const matrix3d & a ) { return a * -1 + k; }
  friend matrix3d operator*( const matrix3d & a, T k )
  {
    return matrix3d( std::to_string( k ) + "*" + a.name(), 3, { a[0] * k, a[1] * k, a[2] * k } );
  }
  friend matrix3d<T> operator*( T k, const matrix3d & a ) { return a * k; }
  friend matrix3d    operator/( const matrix3d & a, T k )
  {
    if( k == 0 )
    {
      throw new std::invalid_argument( "divide by zero" );
    }
    double kinv = 1.0 / k;
    return a * kinv;
  }
  //=======================================================================
  friend vector3d<T> operator*( const matrix3d & m, const vector3d<T> & v )
  {
    if( m.dims() != v.dims() )
    {
      throw new std::invalid_argument( "Dimensions don't match" );
    }
    int         dims = m.dims();
    vector3d<T> new_vec( m.name() + "*" + v.name(), dims );

    for( int j = 0; j <= dims; j++ )
    {
      double dot = 0;
      for( int i = 0; i <= dims; i++ )
      {
        dot += m[i][j] * v[i];
      }
      new_vec[j] = dot;
    }
    return new_vec;
  }
  friend vector3d<T> operator*( const vector3d<T> & v, const matrix3d & m ) { return m * v; }
  matrix3d<T>        operator*( const matrix3d<T> & b );
  //=======================================================================
  matrix3d<T> transpose() const;    // create a new matrix transpose()
  T           determinant() const;
  T           trace() const;
  //=======================================================================
  matrix3d<T> minors() const;                 // see defn
  matrix3d<T> cofactor() const;               // (-1)^(i+j)*minors()(i, j)
  matrix3d<T> adjoint() const;                // cofactor.transpose()
  matrix3d<T> inverse() const;                // adjoint()/determinant()
                                              //=======================================================================
  static matrix3d<T> identity( int dims );    // identity matrix
  static matrix3d<T> zero( int dims );        // zero matrix
                                              //=======================================================================
  bool operator==( const matrix3d<T> & b ) const;
  bool operator!=( const matrix3d<T> & b ) const;
  //=======================================================================
  friend std::ostream & operator<< <>( std::ostream & os, const matrix3d<T> & m );

private:
  void check_equal_dims( const matrix3d<T> & v ) const;
  void check_bounds( int i ) const;
  void swap( T & x, T & y );


  std::string name_;
  int         dims_ {};
  vector3d<T> cols_[4];
  T           data_[16];
};

//================================================================================================
template<typename T>
matrix3d<T>::matrix3d() : matrix3d( "", 3 )
{}
template<typename T>
matrix3d<T>::matrix3d( const std::string & name, int dims ) : name_( name ), dims_( dims )
{
  for( int i = 0; i < 4; ++i )
  {
    cols_[i].name( "col" + std::to_string( i ) );
  }
  std::memset( data_, 0, 16 * sizeof( T ) );
}
template<typename T>
matrix3d<T>::matrix3d( const std::string & name, int dims, const std::initializer_list<vector3d<T>> & li ) :
  matrix3d( name, dims )
{
  int i = 0;
  for( vector3d<T> value : li )
  {
    if( i > dims_ )
    {
      break;
    }
    cols_[i++] = value;
  }
}

template<typename T>
matrix3d<T>::matrix3d( const std::string & name, int dims, const std::initializer_list<T> & li ) :
  matrix3d( name, dims )
{
  int        i = 0;
  matrix3d & m = *this;
  for( const T & value : li )
  {
    m( i / dims, i % dims ) = value;
    ++i;
  }
}
//=================================================================================================
template<typename T>
matrix3d<T> & matrix3d<T>::operator=( T array[9] )
{
  matrix3d & m = *this;
  for( int i = 0; i < 3; ++i )
  {
    for( int j = 0; j < 3; ++i )
    {
      m( i, j ) = array[i + j];
    }
  }
  return *this;
}
template<typename T>
matrix3d<T> & matrix3d<T>::operator=( T k )
{
  return operator=( { k, k, k, k, k, k, k, k, k } );
}
//  matrix3d& m = *this;
//  for (int i = 0; i < 3; ++i) {
//    for (int j = 0; j < 3; ++j) {
//      m(i, j) = k;
//    }
//  }
//  return *this;
//}
//=================================================================================================
template<typename T>
vector3d<T> matrix3d<T>::operator[]( int i ) const
{
  check_bounds( i );
  return cols_[i];
}
template<typename T>
vector3d<T> & matrix3d<T>::operator[]( int i )
{
  check_bounds( i );
  return cols_[i];
}
template<typename T>
T matrix3d<T>::operator()( int row, int col ) const
{
  check_bounds( col );
  return cols_[col][row];
}
template<typename T>
T & matrix3d<T>::operator()( int row, int col )
{
  check_bounds( col );
  return cols_[col][row];
}
template<typename T>
T * matrix3d<T>::opengl_memory( int row, int col )
{
  matrix3d & m      = *this;
  T *        opengl = new T[( row + 1 ) * ( col + 1 )];

  for( int i = 0; i <= row; i++ )
  {
    for( int j = 0; j <= col; j++ )
    {
      T val;
      if( i == row && j == col )
      {
        val = 1;
      }
      else if( i == row || j == col )
      {
        val = 0;
      }
      else
      {
        val = m[i][j];
      }

      opengl[i * ( col + 1 ) + j] = val;
    }
  }

  return opengl;
}
// implement code here
//=================================================================================================
template<typename T>
void matrix3d<T>::name( const std::string & name )
{
  name_ = name;
}
template<typename T>
const std::string & matrix3d<T>::name() const
{
  return name_;
}

template<typename T>
void matrix3d<T>::dims( const int & dims )
{
  dims_ = dims;
}
template<typename T>
int matrix3d<T>::dims() const
{
  return dims_;
}
//=================================== LINEAR ALGEBRA ================================
template<typename T>
matrix3d<T> & matrix3d<T>::operator+=( T k )
{
  matrix3d<T> & a = *this;
  name_           = std::to_string( k ) + "+" + name_;
  for( int i = 0; i < 4; ++i )
  {
    a[i] += k;
  }
  return *this;
}
template<typename T>
matrix3d<T> & matrix3d<T>::operator-=( T k )
{
  return operator+=( -k );
}
template<typename T>
matrix3d<T> & matrix3d<T>::operator*=( T k )
{
  matrix3d<T> & a = *this;
  name_           = std::to_string( k ) + "+" + name_;
  for( int i = 0; i < 4; ++i )
  {
    a[i] *= k;
  }
  return *this;
}
template<typename T>
matrix3d<T> & matrix3d<T>::operator/=( T k )
{
  if( k == 0 )
  {
    throw new std::invalid_argument( "divide by zero" );
  }
  double kinv = 1.0 / k;
  return operator*=( kinv );
}
//=================================================================================================
template<typename T>
matrix3d<T> & matrix3d<T>::operator+=( const matrix3d<T> & b )
{
  matrix3d<T> & a = *this;
  a[0] += b[0];
  a[1] += b[1];
  a[2] += b[2];
  return *this;
}
template<typename T>
matrix3d<T> & matrix3d<T>::operator-=( const matrix3d<T> & b )
{
  return operator+=( b * -1 );
}
//=================================================================================================
template<typename T>
matrix3d<T> matrix3d<T>::operator-()
{
  const matrix3d<T> & a = *this;
  return matrix3d<T>( "-" + name_, 3, { -a[0], -a[1], -a[2] } );
}
template<typename T>
matrix3d<T> matrix3d<T>::operator+( const matrix3d<T> & b )
{
  const matrix3d<T> & a = *this;
  check_equal_dims( b );
  return matrix3d<T>( name_ + "+" + b.name_, dims_, { a[0] + b[0], a[1] + b[1], a[2] + b[2] } );
}
template<typename T>
matrix3d<T> matrix3d<T>::operator-( const matrix3d<T> & b )
{
  return operator+( b * -1 );
}
//=================================================================================================
template<typename T>
matrix3d<T> matrix3d<T>::operator*( const matrix3d<T> & b )
{
  matrix3d            res( name_ + "+" + b.name_, 3 );
  const matrix3d<T> & a = *this;
  for( int i = 0; i < dims_; ++i )
  {
    for( int j = 0; j < dims_; ++j )
    {
      T result = T();
      for( int k = 0; k < dims_; ++k )
      {
        result += a( i, k ) * b( k, j );    // SUM OVER K(a[i][k] * b[k][j]
      }
      res( i, j ) = result;
    }
  }
  return res;
}
//=================================================================================================
template<typename T>
matrix3d<T> matrix3d<T>::transpose() const
{
  const matrix3d<T> & m = *this;
  matrix3d<T>         t( m.name() + "T", m.dims() );

  for( int i = 0; i < m.dims_; i++ )
  {
    for( int j = i; j < m.dims_; j++ )
    {
      if( i == j )
      {
        t[i][j] = m[i][j];
      }
      else
      {
        t[i][j] = m[j][i];
        t[j][i] = m[i][j];
      }
    }
  }

  return t;
}
template<typename T>
T matrix3d<T>::determinant() const
{
  const matrix3d<T> & m = *this;
  return ( m[0][0] * ( m[1][1] * m[2][2] - m[2][1] * m[1][2] ) )
       - ( m[0][1] * ( m[1][0] * m[2][2] - m[2][0] * m[1][2] ) )
       + ( m[0][2] * ( m[1][0] * m[2][1] - m[2][0] * m[1][1] ) );
}
template<typename T>
T matrix3d<T>::trace() const
{
  const matrix3d<T> & m = *this;
  return m( 0, 0 ) + m( 1, 1 ) + m( 2, 2 );
}
//=================================================================================================
//||ef| |df| |de||
//||hi| |gi| |gh||
// | |
//||bc| |ac| |ab||
//||hi| |gi| |gh||
// | |
//||bc| |ac| |ab||
//||ef| |df| |de|| //---------------------------------------------------------------
template<typename T>
matrix3d<T> matrix3d<T>::minors() const
{
  const matrix3d<T> & m = *this;
  return matrix3d<T>( "Min(" + name_ + ")", 3,
                      {
                          m( 1, 1 ) * m( 2, 2 ) - m( 1, 2 ) * m( 2, 1 ),
                          m( 1, 0 ) * m( 2, 2 ) - m( 1, 2 ) * m( 2, 0 ),
                          m( 1, 0 ) * m( 2, 1 ) - m( 1, 1 ) * m( 2, 0 ),

                          m( 0, 1 ) * m( 2, 2 ) - m( 0, 2 ) * m( 2, 1 ),
                          m( 0, 0 ) * m( 2, 2 ) - m( 0, 2 ) * m( 2, 0 ),
                          m( 0, 0 ) * m( 2, 1 ) - m( 0, 1 ) * m( 2, 0 ),

                          m( 0, 1 ) * m( 1, 2 ) - m( 0, 2 ) * m( 1, 1 ),
                          m( 0, 0 ) * m( 1, 2 ) - m( 0, 2 ) * m( 1, 0 ),
                          m( 0, 0 ) * m( 1, 1 ) - m( 0, 1 ) * m( 1, 0 ),
                      } );
}
template<typename T>
matrix3d<T> matrix3d<T>::cofactor() const
{
  const matrix3d<T> & m = minors();
  matrix3d<T>         cof( "Cofactor(" + name_ + ")", m.dims() );

  for( int i = 0; i < dims_; i++ )
  {
    for( int j = 0; j < dims_; j++ )
    {
      cof[i][j] = std::pow( -1, ( i + 1 ) + ( j + 1 ) ) * m[i][j];
    }
  }

  return cof;
}
template<typename T>
matrix3d<T> matrix3d<T>::adjoint() const
{
  return cofactor().transpose();
}
template<typename T>
matrix3d<T> matrix3d<T>::inverse() const
{
  return adjoint() / determinant();
}
//=================================================================================================
template<typename T>
matrix3d<T> matrix3d<T>::identity( int dims )
{
  matrix3d<T> iden( "I" + std::to_string( dims ), dims );

  for( int i = 0; i < dims; i++ )
  {
    iden[i][i] = 1;
  }

  return iden;
}
template<typename T>
matrix3d<T> matrix3d<T>::zero( int dims )
{
  return matrix3d<T>( "zero", dims, { vector3D::zero(), vector3D::zero(), vector3D::zero() } );
}
template<typename T>
bool matrix3d<T>::operator==( const matrix3d<T> & b ) const
{
  check_equal_dims( b );
  const matrix3d<T> & a     = *this;
  T                   error = T();
  for( int i = 0; i < dims_; ++i )
  {
    for( int j = 0; j < dims_; ++j )
    {
      error += std::abs( (double) ( a( i, j ) - b( i, j ) ) );
    }
  }
  return error < epsilon;
}
template<typename T>
bool matrix3d<T>::operator!=( const matrix3d<T> & b ) const
{
  return !( *this == b );
}
//=================================================================================================
// Matrix of minors
//=================================================================================================
template<typename T>
std::ostream & operator<<( std::ostream & os, const matrix3d<T> & m )
{
  os << "<'" << m.name_ << "', ";
  for( int i = 0; i < 3; ++i )
  {
    os << m.cols_[i];
  }
  os << "> OR by rows...\n";
  for( int i = 0; i < 3; ++i )
  {
    for( int j = 0; j < 3; ++j )
    {
      os << std::setw( 3 ) << vector3d<T>::value( m( i, j ) ) << " ";
    }
    os << "\n";
  }
  return os << ">";
}

//=================================================================================================
template<typename T>
void matrix3d<T>::check_equal_dims( const matrix3d<T> & v ) const
{
  if( dims_ != v.dims_ )
  {
    throw new std::invalid_argument( "matrix3d dims mismatch" );
  }
}
template<typename T>
void matrix3d<T>::check_bounds( int i ) const
{
  if( i > dims_ )
  {
    throw new std::invalid_argument( "out of bounds" );
  }
}
template<typename T>
void matrix3d<T>::swap( T & x, T & y )
{
  T temp = x;
  x      = y;
  y      = temp;
}

#endif /* __matrix_3d__ */
