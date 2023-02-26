#include "Ambient.h"

// ---------------------------------------------------------------------- default constructor

Ambient::Ambient ()
	: 	Light(),
		ls(1.0),
		color(1.0)			
{}
// ---------------------------------------------------------------------- copy constructor

Ambient::Ambient (const Ambient& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
{}
// ---------------------------------------------------------------------- clone

Light* 
Ambient::clone() const { return (new Ambient(*this)); }
// ---------------------------------------------------------------------- assignment operator

Ambient& 
Ambient::operator= (const Ambient& rhs) {
    if (this == &rhs) { return (*this); }
	Light::operator= (rhs);
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}
// ---------------------------------------------------------------------- destructor																			

Ambient::~Ambient () {}


void Ambient::scale_radiance(const float b) { ls = b; }

void Ambient::set_color(const float c) { color.r = color.g = color.b = c; }

void Ambient::set_color(const RGBColor& c) { color = c; }

void Ambient::set_color(const float r, const float g, const float b) {
    color.r = r;  color.g = g;  color.b = b;
}
// ---------------------------------------------------------------------- get_direction	

Vector3D								
Ambient::get_direction(ShadeRec&) { return (Vector3D(0.0)); }
// ---------------------------------------------------------------------- L

RGBColor
Ambient::L(ShadeRec&) { return (ls * color); }
