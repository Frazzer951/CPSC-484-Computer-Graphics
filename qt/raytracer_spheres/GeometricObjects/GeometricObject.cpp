#include "Utilities/Constants.h"
#include "Materials/Material.h"
#include "GeometricObject.h"


GeometricObject::GeometricObject() : material_ptr(NULL) { }

GeometricObject::GeometricObject (const GeometricObject& object) {
    if(object.material_ptr)
        material_ptr = object.material_ptr->clone();
    else  material_ptr = NULL;
}

GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) {
    if (this == &rhs) { return (*this); }
    if (material_ptr) {
        delete material_ptr;
        material_ptr = NULL;
    }
    if (rhs.material_ptr) { material_ptr = rhs.material_ptr->clone(); }
    return (*this);
}

GeometricObject::~GeometricObject () {
    if (material_ptr) {
        delete material_ptr;
        material_ptr = NULL;
    }
}

Material* GeometricObject::get_material() const { return (material_ptr); }

void GeometricObject::set_material(Material* mPtr) { material_ptr = mPtr; }

// ---------------------------------------------------------------------- assignment operator
// ---------------------------------------------------------------------- destructor
								
