// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Texture.h"

// ---------------------------------------------------------------- default constructor

Texture::Texture(void) { }


// ---------------------------------------------------------------- copy constructor

Texture::Texture(const Texture& other) : Texture() { copy(other); }


// ---------------------------------------------------------------- assignment operator

Texture& Texture::operator= (const Texture& other) {
    if (this != &other) { copy(other); }
    return (*this);
}


void Texture::copy(const Texture& ) {
    // nothing to copy
}


// ---------------------------------------------------------------- destructor

Texture::~Texture(void) {
}
