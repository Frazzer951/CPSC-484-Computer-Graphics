#ifndef __MATHS__
#define __MATHS__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This is a header file for the mathematics utility functions
// The prototypes of any inlined functions must be placed here

#include <stdlib.h>

#include "Constants.h"
#include "RGBColor.h"

// prototypes

double min( double x0, double x1 );

double max( double x0, double x1 );

int random_int( void );

float random_float( void );

void set_rand_seed( const int seed );

float random_float( int l, float h );

int random_int( int l, int h );

double clamp( const double x, const double min, const double max );

int SolveQuadric( double c[3], double s[2] );

int SolveCubic( double c[4], double s[3] );

int SolveQuartic( double c[5], double s[4] );

// inlined functions

// ----------------------------------------------------------------- min

inline double min( double x0, double x1 ) { return ( ( x0 < x1 ) ? x0 : x1 ); }
// ----------------------------------------------------------------- max

inline double max( double x0, double x1 ) { return ( ( x0 > x1 ) ? x0 : x1 ); }
// ---------------------------------------------------- rand_int
// a wrapper for rand()

inline int random_int( void ) { return ( rand() ); }
// ---------------------------------------------------- rand_float

inline float random_float( void ) { return ( (float) random_int() * invRAND_MAX ); }
// ---------------------------------------------------- set_rand_seed

inline void set_rand_seed( const int seed ) { srand( seed ); }
// The following two functions are only for multi-jittered sampling
// I had trouble getting them to compile in the MultiJittered class
// The overloading confused my compiler

// ---------------------------------------------------- rand_float with arguments

inline float random_float( int l, float h ) { return ( random_float() * ( h - l ) + l ); }
// ---------------------------------------------------- rand_int with arguments

inline int random_int( int l, int h ) { return ( (int) ( random_float( 0, h - l + 1 ) + l ) ); }
// ---------------------------------------------------- clamp

inline double clamp( const double x, const double min, const double max ) { return ( x < min ? min : ( x > max ? max : x ) ); }

#endif
