#ifndef THICKRING_H
#define THICKRING_H

#include "Compound.h"

class ThickRing : public Compound {
public:
  ThickRing( void );
  ThickRing( const double bottom, const double top, const double r1, const double r2 );
  ThickRing( const ThickRing &sc );
  virtual ThickRing *clone( void ) const;
  ThickRing         &operator=( const ThickRing &rhs );
  virtual ~ThickRing( void );

  void set_inner_wall_material( std::shared_ptr<Material> m );
  void set_outer_wall_material( std::shared_ptr<Material> m );
  void set_bottom_material( std::shared_ptr<Material> m );
  void set_top_material( std::shared_ptr<Material> m );

  //  void set_inner_wall_material(Material* m);
  //  void set_outer_wall_material(Material* m);
  //  void set_bottom_material(Material* m);
  //  void set_top_material(Material* m);

  virtual bool hit( const Ray &ray, double &tmin, ShadeRec &sr ) const;
  virtual bool shadow_hit( const Ray &ray, double &tmin ) const;
};

#endif    // THICKRING_H
