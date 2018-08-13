#include "Sphere.h"

Sphere::Sphere(){}
	
Sphere::~Sphere(){}

Sphere::Sphere(double _rad, Vector3 _p, Vector3 _e, Vector3 _c, Refl_t _refl)
	: rad(_rad), p(_p)
{
	e = _e;
	c = _c; 
	refl = _refl;
}

bool Sphere::hit(Ray &r){
	// returns distance, 0 if nohit
	Vector3 op = p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    
	double t;
	double eps = 1e-4;
	double b = op.dot(r.d);
	double det = b * b - op.dot(op) + rad * rad;

    if (det<0) 
		return false; 
	else 
		det=sqrt(det);
    
	t = b-det;
	if(t>eps && t<r.t){
		r.t = t;
		Vector3 x = r.o + r.d * r.t; // the hitting point
		r.n = ( x - p).norm(); // normal at the hitting point
		r.inside = r.n.dot(r.d) > 0;
		return true;
	}

	t = b+det;
	if(t>eps && t<r.t){
		r.t = t;
		Vector3 x = r.o + r.d * r.t; // the hitting point
		r.n = ( x - p).norm(); // normal at the hitting point
		r.inside = r.n.dot(r.d) > 0;
		return true;
	}

	return false;

}