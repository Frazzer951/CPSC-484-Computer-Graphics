#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

//=====================================
// ViewPlane
//=====================================
//
#include "Samplers/Sampler.h"

const int VIEWPLANE_HRES = 1000;    // 500
const int VIEWPLANE_VRES = 1000;    // 500

struct ViewPlane {
  ViewPlane();

  ViewPlane( const ViewPlane &vp );
  ViewPlane &operator=( const ViewPlane &rhs );
  ~ViewPlane() {}

  void set_hres( int h_res ) { hres = h_res; }
  void set_vres( int v_res ) { vres = v_res; }
  void set_pixel_size( float size ) { s = size; }

  void set_gamma( float g ) {
    gamma     = g;
    inv_gamma = 1.0 / gamma;
  }
  void set_gamut_display( bool show ) { show_out_of_gamut = show; }
  void set_samples( int n );
  void set_sampler( Sampler *sp );

  int   hres;           // horizontal image resolution
  int   vres;           // vertical image resolution
  float s;              // pixel size
  int   num_samples;    // number of samples per pixel

  float gamma;                // gamma correction factor
  float inv_gamma;            // the inverse of the gamma correction factor
  bool  show_out_of_gamut;    // display red if RGBColor out of gamut

  static int  max_depth;
  static void set_max_depth( int max );

  Sampler *sampler_ptr;    // ptr to current Sampler object
};

#endif
