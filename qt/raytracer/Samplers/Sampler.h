#ifndef __SAMPLER__
#define __SAMPLER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>
#include <math.h>

#include "Utilities/Point2D.h"
#include "Utilities/Point3D.h"
#include "Utilities/Maths.h"


class Sampler {	
public:
    Sampler(void);
    Sampler(const int num);
    Sampler(const int num, const int num_sets);

    virtual Sampler*  clone(void) const = 0;

    Sampler(const Sampler& s);
    Sampler&
    operator= (const Sampler& rhs);

    virtual  ~Sampler(void);

    void set_num_sets(const int np);
    virtual void  generate_samples(void) = 0;	// generate sample patterns in a unit square

    int get_num_samples(void);

    void shuffle_x_coordinates(void);
    void shuffle_y_coordinates(void);
    void setup_shuffled_indices(void);

    void map_samples_to_unit_disk(void);
    void map_samples_to_hemisphere(const float p);
    void map_samples_to_sphere(void);

    // the following functions are not const because they change count and jump
    Point2D	sample_unit_square(void);  	// get next sample on unit square
    Point2D	sample_unit_disk(void);	   // get next sample on unit disk
    Point3D	sample_hemisphere(void);   // get next sample on unit hemisphere
    Point3D	sample_sphere(void);	   // get next sample on unit sphere
    Point2D	sample_one_set(void);	   // only used to set up a vector noise table
                                       // this is not discussed in the book, but see the
                                       // file LatticeNoise.cpp in Chapter 31
protected:
    int 					num_samples;     		// the number of sample points in a set
    int 					num_sets;				// the number of sample sets
    std::vector<Point2D>	samples;				// sample points on a unit square
    std::vector<int>		shuffled_indices;		// shuffled samples array indices
    std::vector<Point2D>	disk_samples;			// sample points on a unit disk
    std::vector<Point3D> 	hemisphere_samples;		// sample points on a unit hemisphere
    std::vector<Point3D> 	sphere_samples;			// sample points on a unit sphere
    unsigned long 			count;					// the current number of sample points used
    int 					jump;					// random index jump
};

#endif

