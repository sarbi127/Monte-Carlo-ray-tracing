#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vector3.h"

class Sphere : public Object
{
public:
    Sphere();
	~Sphere();

	Sphere(double _rad, Vector3 _p, Vector3 _e, Vector3 _c, Refl_t _refl);

	bool hit(Ray &r);
	
	inline Vector3 get_color(){ return c;};
	inline Refl_t get_refl(){ return refl;};
	inline Vector3 get_emi(){ return e;};

private:
    double rad; // radius
	Vector3 p;  // position

};
#endif