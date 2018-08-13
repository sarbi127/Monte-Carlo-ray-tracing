#include "Rectangle.h"
#include <math.h>

Rectangle::Rectangle(){}

/*
Rectangle::Rectangle(double _size, Vector3 _p, Vector3 _n, Vector3 _e, Vector3 _c, Refl_t _refl)
	: size(_size), p(_p)
{
	n = _n;
	e = _e;	
	c = _c; 
	refl = _refl;
}
*/

Rectangle::~Rectangle(){}


Rectangle::Rectangle(Vector3 _v0, Vector3 _v1, Vector3 _v2, Vector3 _v3, Vector3 _e, Vector3 _c, Refl_t _refl)
	: v0(_v0), v1(_v1), v2(_v2), v3(_v3)
{
	e = _e;	
	c = _c; 
	refl = _refl;

	n = ((v1-v0).cross(v1-v2)).norm();
}

bool Rectangle::hit(Ray &r){
	// split the rectangle in to two triangles and test hit
	double eps = 1e-4;
	Vector3 p, e1, e2, e3;
	double dot11, dot12, dot13, dot22, dot23, u, v;

	double t = -((r.o-v0).dot(n))/r.d.dot(n);

	// First triangle {v0, v1, v2}
	if(t>=eps && t<r.t){
		p = r.o + r.d * t;
		e1 = v1 - v0;
		e2 = v2 - v0;
		e3 = p - v0;

		dot11 = e1.dot(e1);
		dot12 = e1.dot(e2);
		dot13 = e1.dot(e3);
		dot22 = e2.dot(e2);
		dot23 = e2.dot(e3);

		u = (dot22 * dot13 - dot12 * dot23) / (dot11 * dot22 - dot12 * dot12);
		v = (dot11 * dot23 - dot12 * dot13) / (dot11 * dot22 - dot12 * dot12);

		if (u >= 0.0 && v >= 0.0 && u+v < 1.0 + eps){
			r.inside = false;
			r.t = t;
			r.n = n;			
			return true;
		}
	}

	// Second triangle {v0, v2, v3}
	t = -((r.o-v2).dot(n))/r.d.dot(n);
	if(t>=eps && t<r.t){
		p = r.o + r.d * t;
		e1 = v0 - v2;
		e2 = v3 - v2;
		e3 = p - v2;

		dot11 = e1.dot(e1);
		dot12 = e1.dot(e2);
		dot13 = e1.dot(e3);
		dot22 = e2.dot(e2);
		dot23 = e2.dot(e3);

		u = (dot22 * dot13 - dot12 * dot23) / (dot11 * dot22 - dot12 * dot12);
		v = (dot11 * dot23 - dot12 * dot13) / (dot11 * dot22 - dot12 * dot12);

		if (u >= 0.0 && v >= 0.0 && u+v < 1.0 + eps){
			r.inside = false;
			r.t = t;
			r.n = n;			
			return true;
		}
	}

	return false;
}

/*
double Rectangle::hit(Ray &r){
	double eps = 1e-4;
	Vector3 pd = p - r.o;
	double pd_dot_n = pd.dot(n);
	double rd_dot_n = r.d.dot(n);

	if(rd_dot_n == 0)
		return 0;

	double t = pd_dot_n/rd_dot_n;

	if(t>eps && t<r.t){
		Vector3 hp = r.o + r.d * r.t; // the hitting point
		
		if(n == Vector3(0,1,0)||n==Vector3(0,-1,0)){
			if(abs(hp.x - p.x)>size/2.0) 
				return 0;
			if(abs(hp.z - p.z)>size/2.0) 
				return 0;
		}
		else if(n == Vector3(1,0,0)||n==Vector3(-1,0,0)){
			if(abs(hp.y - p.y)>size/2.0) 
				return 0;
			if(abs(hp.z - p.z)>size/2.0) 
				return 0;
		}
		else if(n == Vector3(0,0,1)||n==Vector3(0,0,-1)){
			if(abs(hp.x - p.x)>size/2.0) 
				return 0;
			if(abs(hp.y - p.y)>size/2.0) 
				return 0;
		}
		r.inside = r.n.dot(r.d) > 0;
		r.t = t;
		r.n = n;
		return t;
	}

	return 0;

}
*/
