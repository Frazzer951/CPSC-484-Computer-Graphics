// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Mesh.h"

// ----------------------------------------------------------------  default constructor

Mesh::Mesh( void ) : num_vertices( 0 ), num_triangles( 0 ) {}

Mesh::Mesh( const Mesh &other ) : Mesh() { copy( other ); }

Mesh &Mesh::operator=( const Mesh &other ) {
  if ( this != &other ) { copy( other ); }
  return ( *this );
}

void Mesh::copy( const Mesh &other ) {
  vertices      = other.vertices;
  normals       = other.normals;
  u             = other.u;
  v             = other.v;
  num_vertices  = other.num_vertices;
  num_triangles = other.num_triangles;
}

// ---------------------------------------------------------------- destructor

Mesh::~Mesh( void ) {}
