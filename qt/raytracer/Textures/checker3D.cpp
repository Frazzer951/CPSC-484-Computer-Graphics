#include "Checker3D.h"

Checker3D::Checker3D(void)
: Texture(),
  size(1.0),
  color1(1.0),
  color2(0.0) {
}


Checker3D::Checker3D(const Checker3D& other)
: Checker3D() { copy(other); }


Checker3D& Checker3D::operator= (const Checker3D& other) {
    if (this != &other) { copy(other); }
    return *this;
}


void Checker3D::copy(const Checker3D& other) {
    Texture::operator=(other);

    size = other.size;
    color1 = other.color1;
    color2 = other.color2;
}


Checker3D::~Checker3D (void) { }


Checker3D* Checker3D::clone(void) const { return new Checker3D (*this); }


void Checker3D::set_size(const float s) { size = s; }

void Checker3D::set_color1(const RGBColor& c) { color1 = c; }

void Checker3D::set_color1(const float c) { color1.r = color1.g = color1.b = c; }

void Checker3D::set_color1(const float r, const float g, const float b) {
  color1.r = r;  color1.g = g;  color1.b = b;
}

void Checker3D::set_color2(const RGBColor& c) { color2 = c; }

void Checker3D::set_color2(const float c) { color2.r = color2.g = color2.b = c; }

void Checker3D::set_color2(const float r, const float g, const float b) {
  color2.r = r;   color2.g = g;   color2.b = b;
}

RGBColor Checker3D::get_color(const ShadeRec& sr) const { 
      float eps = -0.000187453738; // small random number
      float x = sr.local_hit_point.x + eps;
      float y = sr.local_hit_point.y + eps;
      float z = sr.local_hit_point.z + eps;

      if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / 
            size)) % 2 == 0) return (color1);
      else
            return (color2);
}
