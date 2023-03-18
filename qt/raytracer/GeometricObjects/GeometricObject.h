#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;

#include <memory>

#include "Utilities/BBox.h"
#include "Utilities/Constants.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/Normal.h"
#include "Utilities/Ray.h"
#include "Utilities/ShadeRec.h"

class Material;

//=====================================
// GeometricObject
//=====================================
//
class GeometricObject {
public:
  GeometricObject( void );
  GeometricObject( const GeometricObject &object );

  virtual GeometricObject *clone( void ) const = 0;
  virtual ~GeometricObject( void );

  virtual bool hit( const Ray &ray, double &t, ShadeRec &s ) const = 0;
  virtual bool shadow_hit( const Ray &ray, double &tmin ) const    = 0;

  virtual void                                           // This needs to be virtual so that it can be overridden in Compound
      set_material( std::shared_ptr<Material> mPtr );    // It therefore shouldn't be inlined
  //    set_material(Material* mPtr); 			// It therefore shouldn't be inlined

  std::shared_ptr<Material> get_material( void ) const;

  // The following three functions are only required for Chapter 3
  void set_color( const RGBColor &c );
  void set_color( const float r, const float g, const float b );

  RGBColor get_color( void );

  virtual void set_bounding_box( void );
  virtual BBox get_bounding_box( void );

  virtual void add_object( GeometricObject *object_ptr );    // required for compound objects

  // The following two functions are only required for objects that are light sources, eg disks, rects, and spheres
  virtual Point3D sample( void );

  virtual float pdf( ShadeRec &sr );

  // The following two functions allow us to simplify the code for smooth shaded triangle meshes
  virtual Normal get_normal( void ) const;
  virtual Normal get_normal( const Point3D &p );

protected:
  mutable std::shared_ptr<Material> material_ptr;    // mutable allows the const functions Compound::hit,
                                                     //     Instance::hit, and RegularGrid::hit to assign to material_ptr
  RGBColor                          color;           // only used for Bare Bones ray tracing

  GeometricObject &operator=( const GeometricObject &rhs );

  bool shadows;
};

// --------------------------------------------------------------------  set_color
inline void GeometricObject::set_color( const RGBColor &c ) { color = c; }
// --------------------------------------------------------------------  set_color

inline void GeometricObject::set_color( const float r, const float g, const float b ) {
  color.r = r;
  color.b = b;
  color.g = g;
}
// --------------------------------------------------------------------  get_color

inline RGBColor GeometricObject::get_color( void ) { return ( color ); }

#endif
