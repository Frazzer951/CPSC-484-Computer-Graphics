#include "Emissive.h"
#include "Matte.h"

Emissive::Emissive( void ) : Material(), ls( 1.0 ), ce( 1.0 ) {}

Emissive::Emissive( const Emissive &other ) : Emissive() { copy( other ); }

Emissive &Emissive::operator=( const Emissive &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void Emissive::copy( const Emissive &other ) {
  Material::operator=( other );

  ls = other.ls;
  ce = other.ce;
}

Emissive *Emissive::clone( void ) const { return new Emissive( *this ); }

Emissive::~Emissive( void ) {}

RGBColor Emissive::get_Le( ShadeRec & /*sr*/ ) const { return ls * ce; }

RGBColor Emissive::shade( ShadeRec &sr ) { return sr.color; }
#include <QDebug>
RGBColor Emissive::area_light_shade( ShadeRec &sr ) {
  //qDebug() << "Emissive::area_light_shade";
  if ( -sr.normal.dot( sr.ray.d ) > 0.0 )
    return ls * ce;
  else
    return black;
}
