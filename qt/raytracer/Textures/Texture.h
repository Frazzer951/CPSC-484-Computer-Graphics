#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Utilities/RGBColor.h"
#include "Utilities/Matrix.h"
#include "Utilities/ShadeRec.h"
#include <math.h>


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

class Texture {
public:
  Texture(void);
  Texture(const Texture& other);
  virtual ~Texture(void);
  virtual Texture* clone(void) const = 0;

  virtual RGBColor get_color(const ShadeRec& sr) const = 0;

private:
  void copy(const Texture& other);

protected:
  Texture& operator= (const Texture& other);
};

#endif
