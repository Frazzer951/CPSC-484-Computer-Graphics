#include "ImageTexture.h"

#include <cstdlib>

// ---------------------------------------------------------------- default constructor

ImageTexture::ImageTexture( void ) : Texture(), hres( 100 ), vres( 100 ), image_ptr( NULL ), mapping_ptr( NULL ) {}

// ---------------------------------------------------------------- constructor

ImageTexture::ImageTexture( Image *_image_ptr ) :
    Texture(), hres( _image_ptr->get_hres() ), vres( _image_ptr->get_vres() ), image_ptr( _image_ptr ), mapping_ptr( NULL ) {}

// ---------------------------------------------------------------- copy constructor

ImageTexture::ImageTexture( const ImageTexture &it ) : Texture( it ), hres( it.hres ), vres( it.vres ) {
  if ( image_ptr ) {
    delete image_ptr;
    image_ptr = NULL;
  }
  if ( it.image_ptr ) { image_ptr = it.image_ptr->clone(); }

  if ( mapping_ptr ) {
    delete mapping_ptr;
    mapping_ptr = NULL;
  }
  if ( it.mapping_ptr ) { mapping_ptr = it.mapping_ptr->clone(); }

  if ( it.image_ptr ) {
    *image_ptr = *it.image_ptr;
  } else {
    image_ptr = NULL;
  }

  if ( it.mapping_ptr ) {
    mapping_ptr = it.mapping_ptr->clone();
  } else {
    mapping_ptr = NULL;
    ;
  }
}

// ---------------------------------------------------------------- assignment operator

ImageTexture &ImageTexture::operator=( const ImageTexture &it ) {
  if ( this == &it ) { return ( *this ); }

  Texture::operator=( it );

  hres = it.hres;
  vres = it.vres;

  if ( image_ptr ) {
    delete image_ptr;
    image_ptr = NULL;
  }
  if ( it.image_ptr ) { image_ptr = it.image_ptr->clone(); }

  if ( mapping_ptr ) {
    delete mapping_ptr;
    mapping_ptr = NULL;
  }
  if ( it.mapping_ptr ) { mapping_ptr = it.mapping_ptr->clone(); }

  if ( image_ptr ) { image_ptr = NULL; }

  if ( it.image_ptr ) { *image_ptr = *it.image_ptr; }

  if ( mapping_ptr ) { mapping_ptr = NULL; }

  if ( it.mapping_ptr ) { mapping_ptr = it.mapping_ptr->clone(); }
  return ( *this );
}

// ---------------------------------------------------------------- clone

ImageTexture *ImageTexture::clone( void ) const { return ( new ImageTexture( *this ) ); }

// ---------------------------------------------------------------- destructor

ImageTexture::~ImageTexture( void ) {
  if ( image_ptr ) { delete image_ptr; }
  if ( mapping_ptr ) { delete mapping_ptr; }
}

// ---------------------------------------------------------------- set_image
void ImageTexture::set_image( Image *_image_ptr ) {
  image_ptr = _image_ptr;
  hres      = image_ptr->get_hres();
  vres      = image_ptr->get_vres();
}

// ---------------------------------------------------------------- set_mapping
//void               set_mapping(Mapping* map_ptr);
void ImageTexture::set_mapping( Mapping *map_ptr ) { mapping_ptr = map_ptr; }

// ---------------------------------------------------------------- get_color

// When we ray trace a triangle mesh object with uv mapping, the mapping pointer may be NULL
// because we can define uv coordinates on an arbitrary triangle mesh.
// In this case we don't use the local hit point because the pixel coordinates are computed
// from the uv coordinates stored in the ShadeRec object in the uv triangles' hit functions
// See, for example, Listing 29.12.

RGBColor ImageTexture::get_color( const ShadeRec &sr ) const {
  int row, column;

  if ( mapping_ptr ) {
    mapping_ptr->get_texel_coordinates( sr.local_hit_point, hres, vres, row, column );
  } else {
    row    = (int) ( sr.v * ( vres - 1 ) );
    column = (int) ( sr.u * ( hres - 1 ) );
  }

  return ( image_ptr->get_color( row, column ) );
}
