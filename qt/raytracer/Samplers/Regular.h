#ifndef __REGULAR__
#define __REGULAR__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"


class Regular: public Sampler {
public:
    Regular(void);
    Regular(const int num);

    virtual Regular*  clone(void) const;

    Regular(const Regular& u);
    Regular&
    operator= (const Regular& rhs);

    virtual ~Regular(void);

//private:  // missing private in orig. code?
    virtual void  generate_samples(void);
};

#endif

