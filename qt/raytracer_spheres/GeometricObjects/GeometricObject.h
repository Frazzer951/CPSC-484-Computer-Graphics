#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;
	
#include "Utilities/Point3D.h"
#include "Utilities/Ray.h"
#include "Utilities/ShadeRec.h"


//=====================================
// GeometricObject
//=====================================
//
class GeometricObject {
public:
    GeometricObject();

    GeometricObject(const GeometricObject& object);
protected:
    GeometricObject& operator=(const GeometricObject& rhs);

public:
    virtual GeometricObject* clone() const = 0;
    virtual ~GeometricObject ();

    virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

    Material* get_material() const;
    virtual void set_material(Material* mPtr);

protected:
    // mutable allows Compound::hit, Instance::hit and Grid::hit
    //     to assign to material_ptr. hit functions are const
    mutable Material* material_ptr;
};


#endif
