#include "SV_Emissive.h"
#include "Matte.h"

SV_Emissive::SV_Emissive( void ) : Material(), ls( 1.0 ), ce( NULL ) {}

SV_Emissive::SV_Emissive( const SV_Emissive &other ) : SV_Emissive() { copy( other ); }

SV_Emissive &SV_Emissive::operator=( const SV_Emissive &other ) {
  if ( this != &other ) { copy( other ); }
  return *this;
}

void SV_Emissive::copy( const SV_Emissive &other ) {
  Material::operator=( other );

  ls = other.ls;
  ce = other.ce;
}

SV_Emissive *SV_Emissive::clone( void ) const { return new SV_Emissive( *this ); }

SV_Emissive::~SV_Emissive( void ) {}

RGBColor SV_Emissive::get_Le( ShadeRec &sr ) const { return ls * ce->get_color( sr ); }

RGBColor SV_Emissive::shade( ShadeRec &sr ) { return ls * ce->get_color( sr ); }

RGBColor SV_Emissive::area_light_shade( ShadeRec &sr ) {
  //qDebug() << "SV_Emissive::area_light_shade";
  if ( -sr.normal.dot( sr.ray.d ) > 0.0 ) {
    return ls * ce->get_color( sr );
  } else {
    return black;
  }
}
