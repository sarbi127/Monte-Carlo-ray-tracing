#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Object.h"
#include "Vector3.h"

class Rectangle : public Object {
public:
	Rectangle();
	~Rectangle();

	//Rectangle(double _size, Vector3 _p, Vector3 _n, Vector3 _e, Vector3 _c, Refl_t _refl);

	Rectangle(Vector3 _v0, Vector3 _v1, Vector3 _v2, Vector3 _v3, Vector3 _e, Vector3 _c, Refl_t _refl);

	bool hit(Ray &r);
	
	inline Vector3 get_color(){ return c;};
	inline Refl_t get_refl(){ return refl;};
	inline Vector3 get_emi(){ return e;};

private:
	Vector3 n; // normal
	
	Vector3 v0; // vertex 0
	Vector3 v1; // vertex 1
	Vector3 v2; // vertex 2
	Vector3 v3; // vertex 3

};

#endif
