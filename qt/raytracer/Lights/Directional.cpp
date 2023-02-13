#include "Directional.h"

// ---------------------------------------------------------------------- default constructor


Directional::Directional()
	: 	Light(),
		ls(1.0),
		color(1.0),
		dir(0, 1, 0)			
{}


// ---------------------------------------------------------------------- dopy constructor

Directional::Directional(const Directional& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		dir(dl.dir)  		
{}
// ---------------------------------------------------------------------- clone

Light* 
Directional::clone() const {
	return (new Directional(*this));
}
// ---------------------------------------------------------------------- assignment operator

Directional& 
Directional::operator= (const Directional& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	dir 	= rhs.dir;

	return (*this);
}

// ---------------------------------------------------------------------- destructor																			

Directional::~Directional() {}

void Directional::scale_radiance(const float b)  { ls = b; }

void Directional::set_color(const float c) { color.r = color.g = color.b = c; }

void Directional::set_color(const RGBColor& c) { color = c; }

void Directional::set_color(const float r, const float g, const float b) {
    color.r = r;  color.g = g;  color.b = b;
}

void Directional::set_direction(Vector3D d) { dir = d;  dir.normalize(); }

void Directional::set_direction(float dx, float dy, float dz) {
    dir.x = dx;  dir.y = dy;  dir.z = dz;  dir.normalize();
}



// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
Directional::get_direction(ShadeRec&) {
	return (dir);
}	

// ------------------------------------------------------------------------------  L

RGBColor
Directional::L(ShadeRec&) {
	return (ls * color);
}


