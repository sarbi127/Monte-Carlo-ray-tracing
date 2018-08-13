#include "Ray.h"

Ray::Ray(Vector3 _o, Vector3 _d)
	: o(_o), d(_d)
{
	t = 1e20;
	inside = false;
}
	
Ray::~Ray(){}