#ifndef __RGB_COLOR__
#define __RGB_COLOR__

#include <math.h>


//=====================================
// RGBColor
//=====================================
//
struct RGBColor {
    RGBColor() : RGBColor(0.0, 0.0, 0.0) { }
    RGBColor(float c) : RGBColor(c, c, c) { }
    RGBColor(float _r, float _g, float _b) : r(_r), g(_g), b(_b) { }

    RGBColor(const RGBColor& c) : RGBColor(c.r, c.g, c.b) { }
    RGBColor& operator=(const RGBColor& o) {
        if (this == &o) { return (*this); }
        r = o.r; g = o.g; b = o.b;
        return (*this);
    }
    ~RGBColor() { }


    RGBColor operator+(const RGBColor& c) const { return RGBColor(r + c.r, g + c.g, b + c.b); }
    RGBColor& operator+=(const RGBColor& c)     { r += c.r; g += c.g; b += c.b;  return *this; }

    RGBColor operator*(float k) const            { return RGBColor(k * r, k * g, k * b); }
    friend RGBColor operator*(float k,
                              const RGBColor& c) { return c * k; }
    RGBColor& operator*=(float k)                { r *= k; g *= k; b *= k;   return *this; }

    RGBColor operator/(float k) const            { return RGBColor(r/k, g/k, b/k); }
    RGBColor& operator/=(float k)                { r /= k;  g /= k;  b /= k;  return *this; }

    RGBColor operator*(const RGBColor& c) const  { return RGBColor(r * c.r, g * c.g, b * c.b); }

    bool operator==(const RGBColor& c) const     { return (r == c.r && g == c.g && b == c.b); }

            // raise each component to the specified power
                        // used for color filtering in Chapter 28
    RGBColor powc(float p) const                 { return (RGBColor(pow(r, p), pow(g, p), pow(b, p))); }
    float average() const                        { return 0.333333333333 * (r + g + b); }


    float  r, g, b;
};


#endif




