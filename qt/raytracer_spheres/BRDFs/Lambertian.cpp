//#include "brdfs_Lambertian.h"
//#include "utilities_Constants.h"

//// ---------------------------------------------------------------------- default constructor

//Lambertian::Lambertian()
//	:   BRDF(),
//		kd(0.0),
//		cd(0.0)
//{}


//// ---------------------------------------------------------------------- copy constructor

//Lambertian::Lambertian(const Lambertian& lamb)
//	:   BRDF(lamb),
//		kd(lamb.kd),
//		cd(lamb.cd)
//{}


//// ---------------------------------------------------------------------- clone

//Lambertian*
//Lambertian::clone() const {
//	return (new Lambertian(*this));
//}


//// ---------------------------------------------------------------------- destructor

//Lambertian::~Lambertian() {}


//// ---------------------------------------------------------------------- assignment operator

//Lambertian&
//Lambertian::operator= (const Lambertian& rhs) {
//	if (this == &rhs)
//		return (*this);
		
//	BRDF::operator= (rhs);
	
//	kd = rhs.kd;
//	cd = rhs.cd;
	
//	return (*this);
//}


//// ---------------------------------------------------------------------- f

//RGBColor
//Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
//	return (kd * cd * invPI);
//}


//// ---------------------------------------------------------------------- rho

//RGBColor
//Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
//	return (kd * cd);
//}


