#ifndef __MATERIAL__
#define __MATERIAL__

#include "World/World.h"			// required for the shade function in all derived classes
#include "Utilities/RGBColor.h"
#include "Utilities/ShadeRec.h"
#include "Materials/Material.h"


//=====================================
// Material
//=====================================
//
class Material {
public:
    Material();
    Material(const Material&);
protected:
    Material& operator=(const Material& rhs);  // does nothing

public:
    virtual ~Material();
    virtual Material* clone() const = 0;

    virtual RGBColor shade(ShadeRec&);
};

#endif



