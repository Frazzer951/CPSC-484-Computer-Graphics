#ifndef __CHECKER3D__
#define __CHECKER3D__

#include "Texture.h"


class Checker3D: public Texture {
public:
  Checker3D(void);
  Checker3D(const Checker3D& ch);
  Checker3D& operator= (const Checker3D& rhs);
  virtual Checker3D* clone(void) const;
  virtual ~Checker3D(void);

  virtual RGBColor get_color(const ShadeRec& sr) const;

  void set_size(const float s);

  void set_color1(const RGBColor& c);
  void set_color1(const float r, const float g, const float b);
  void set_color1(const float c);

  void set_color2(const RGBColor& c);
  void set_color2(const float r, const float g, const float b);
  void set_color2(const float c);

private:
  void copy(const Checker3D& other);

  float size;
  RGBColor color1;
  RGBColor color2;
};



#endif
