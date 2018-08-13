#ifndef RAY_H
#define RAY_H
#include "Vector3.h"

class Ray{
public:
	Ray(Vector3 _o, Vector3 _d);
	~Ray();

	Vector3 o; // the origin
	Vector3 d; // the direction

	Vector3 n; // normal at hitting point

	bool inside; // ray inside object

	double t; // hitting distance

};

#endif
