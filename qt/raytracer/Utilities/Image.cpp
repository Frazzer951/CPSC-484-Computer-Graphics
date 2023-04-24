// 	Copyright (C) Kevin Suffern 2000-2007.
// 	Copyright (C) Stefan Brumme 2005.
// 	Copyright (C) Sverre Kvaale 2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <QtDebug>

#include <iostream>
#include <stdio.h>

#include "Constants.h"    // defines red
#include "Image.h"

Image::Image( void ) : hres( 100 ), vres( 100 ), pixels() {}

Image::Image( const Image &other ) : Image() { copy( other ); }

Image &Image::operator=( const Image &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void Image::copy( const Image &other ) {
  hres   = other.hres;
  vres   = other.vres;
  pixels = other.pixels;
}

Image *Image::clone( void ) const { return ( new Image( *this ) ); }

Image::~Image( void ) {}

// ---------------------------------------------------- read_ppm_file

void Image::read_ppm_file( const char *file_name ) {
  // read-only binary sequential access
  FILE *file = fopen( file_name, "rb" );

  if ( file == 0 ) {
    qDebug() << "could not open file: " << file_name << Qt::endl;
    return;
  }
  qDebug() << "file: " << file_name << " opened";

  // PPM header
  unsigned char ppm_type;
  if ( fscanf( file, "P%c\n", &ppm_type ) != 1 ) {
    qDebug() << "Invalid PPM signature\n";
    return;
  }

  // only binary PPM supported
  if ( ppm_type != '6' ) {
    qDebug() << "Only binary PPM supported" << Qt::endl;
    return;
  }

  // skip comments
  unsigned char dummy;
  while ( fscanf( file, "#%c", &dummy ) ) {
    while ( fgetc( file ) != '\n' )
      ;
  }

  qDebug() << "comments skipped successfully, reading image file...\n";

  // read image size
  if ( fscanf( file, "%d %d\n", &hres, &vres ) != 2 ) {
    qDebug() << "Invalid image size" << Qt::endl;
    return;
  }

  if ( hres <= 0 ) { qDebug() << "Invalid image width\n"; }
  qDebug() << "hres = " << hres << Qt::endl;

  if ( vres <= 0 ) {
    qDebug() << "Invalid image height" << Qt::endl;
    return;
  }
  qDebug() << "vres = " << vres << Qt::endl;

  // maximum value to be found in the PPM file (usually 255)
  unsigned int max_value;
  if ( fscanf( file, "%d\n", &max_value ) != 1 ) {
    qDebug() << "Invalid max value" << Qt::endl;
    return;
  }

  float inv_max_value = 1.0 / (float) max_value;

  // allocate memory
  pixels.reserve( hres * vres );

  // read pixel data
  unsigned char red, green, blue;
  for ( int y = 0; y < vres; y++ ) {
    for ( int x = 0; x < hres; x++ ) {
      if ( fscanf( file, "%c%c%c", &red, &green, &blue ) != 3 ) { qDebug() << "Invalid image" << Qt::endl; }
      float r = red * inv_max_value;
      float g = green * inv_max_value;
      float b = blue * inv_max_value;
      pixels.push_back( RGBColor( r, g, b ) );
    }
  }

  fclose( file );
  qDebug() << "finished reading PPM file" << Qt::endl;
}

// --------------------------------------------------------------------------------------------- get_color

RGBColor Image::get_color( const int row, const int column ) const {
  int index       = column + hres * ( vres - row - 1 );
  int pixels_size = pixels.size();

  if ( index < pixels_size )
    return ( pixels[index] );
  else
    return ( red );    // useful for debugging
}
