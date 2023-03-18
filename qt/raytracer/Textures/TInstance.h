#ifndef __THINSTANCE__
#define __THINSTANCE__

#include "Texture.h"

class TInstance : public Texture {
public:
  // constructors, etc.

  void set_texture( Texture *t_ptr );

  virtual RGBColor get_color( const ShadeRec &sr ) const;

  // affine tranformation functions:
  void scale( const float sx, const float sy, const float sz );

  // other affine transformations

private:
  Texture *texture_ptr;    // texture being transformed
  Matrix   inv_matrix;     // inverse transformation matrix
};

#endif
