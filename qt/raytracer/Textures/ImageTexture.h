#ifndef __IMAGETEXTURE__
#define __IMAGETEXTURE__

#include "Utilities/Image.h"
#include "Mappings/Mapping.h"
#include "Texture.h"

class ImageTexture : public Texture {
public:
  ImageTexture( void );
  ImageTexture( Image *_image_ptr );
  ImageTexture( const ImageTexture &it );
  virtual ~ImageTexture( void );

  ImageTexture &operator=( const ImageTexture &rhs );

  virtual ImageTexture *clone( void ) const;

  virtual RGBColor get_color( const ShadeRec &sr ) const;

  void set_image( Image *_image_ptr );
  void set_mapping( Mapping *map_ptr );

private:
  int      hres;           // horizontal resolution of the image
  int      vres;           // vertical resolution of the image
                           //    std::shared_ptr<Image>		image_ptr;		// the image
                           //    std::shared_ptr<Mapping>	mapping_ptr;	// mapping technique used, if any
  Image   *image_ptr;      // the image
  Mapping *mapping_ptr;    // mapping technique used, if any
};

#endif
