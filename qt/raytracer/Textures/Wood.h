#ifndef __WOOD__
#define __WOOD__

// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Utilities/RGBColor.h"
#include "Noises/LatticeNoise.h"
#include "Texture.h"

// This class defines a procedural texture based on the Larry Gritz Renderman wood texture described in Apodaca and Gritz (2000).
// The rings here are centered on the y axis, instead of the z axis as in Apodaca and Gritz.
// This is not a complete implementation because it does not do the intrinsic antialiasing that the Renderman version does.

// The following description of the parameters is largely based on code comments in Apodaca and Gritz.

// 		light_color: 				The light background color of the wood.
// 		dark_color: 				The darker color of the rings and grain.
//		ring_frequency:				The mean radial distance berween the rings.
//		ring_uneveness:				If this is zero, the rings are equally spaced and have equal thickness.
//									If this is greater than zero, the rings are unequally spaced and have different thicknesses.

//		ring_noise:					These two parameters just perturb the hit point. The default value of ring_noise is 0.02, and if you
//		ring_noise_frequency:		make ring_noise = 1.0, the wood is destroyed. The wood still looks good with these parameters set to zero.

//		trunk_wobble:				These two parameters perturb the trunk with a noise function so that it's not exactly along the y axis.
//		trunk_wobble_frequency:		trunk_wobble determines the noise amplitude, and trunk_wobble_frequency determines its spatial frequency.

//		angular_wobble:				These two parameters add noise to the rings so that they are not exactly round; angular_wobble specifies
//		angular_wobble_frequency:	the magnitude of the noise, and	angular_wobble_frequency specifies how quckly it varies around the rings.

//		grain_frequency:			This seems to control the size of the grain.

//		grainy:						This is grain-nee, not grain "y". It should be in the range [0, 1]. It determines how the grain is weighted
//									in the shading. With grainy = 0 there is no grain; with grainy = 1, the grain is fully shaded.

//		ringy:						This is ring-ee, not ring "y". It should be in the range [0, 1]. It determines how the rings are weighted
//									in the shading. With ringy = 0 there are no rings; with ringy = 1, the rings are fully shaded.

// All these parameters have default values. The easiest way to experiment with different values is to use the first or second constructor, and
// the access functions, which are supplied for each parameter.

class Wood : public Texture {
public:
  Wood( void );
  Wood( const RGBColor light, const RGBColor dark );
  Wood( LatticeNoise *noise_ptr, const RGBColor light_color, const RGBColor dark_color, const double ring_frequency,
        const double ring_uneveness, const double ring_noise, const double ring_noise_frequency, const double trunk_wobble,
        const double trunk_wobble_frequency, const double angular_wobble, const double angular_wobble_frequency,
        const double grain_frequency, const double grainy, const double ringy );

  Wood( const Wood &wood );
  Wood         &operator=( const Wood &rhs );
  virtual Wood *clone( void ) const;

  ~Wood( void );

  virtual RGBColor get_color( const ShadeRec &sr ) const;

  // access functions:
  void set_noise( LatticeNoise *noise_ptr );

  // noise parameters:
  void set_num_octaves( const int _num_octaves );
  void set_lacunarity( const float _lacunarity );
  void set_gain( const float _gain );

  // wood parameters:
  void set_light_color( const RGBColor &c );
  void set_light_color( const float r, const float g, const float b );
  void set_light_color( const float c );

  void set_dark_color( const RGBColor &c );
  void set_dark_color( const float r, const float g, const float b );
  void set_dark_color( const float c );

  void set_ring_frequency( const double _ring_frequency );
  void set_ring_uneveness( const double _ring_uneveness );
  void set_ring_noise( const double _ring_noise );
  void set_ring_noise_frequency( const double _ring_noise_frequency );

  void set_trunk_wobble( const double _trunk_wobble );
  void set_trunk_wobble_frequency( const double _trunk_wobble_frequency );

  void set_angular_wobble( const double _angular_wobble );
  void set_angular_wobble_frequency( const double _angular_wobble_frequency );

  void set_grain_frequency( const double _grain_frequency );
  void set_grainy( const double _grainy );

  void set_ringy( const double _ringy );

private:
  LatticeNoise *noise_ptr;
  RGBColor      light_color;
  RGBColor      dark_color;

  double ring_frequency;
  double ring_uneveness;
  double ring_noise;
  double ring_noise_frequency;

  double trunk_wobble;
  double trunk_wobble_frequency;

  double angular_wobble;
  double angular_wobble_frequency;

  double grain_frequency;
  double grainy;
  double ringy;
};

#endif