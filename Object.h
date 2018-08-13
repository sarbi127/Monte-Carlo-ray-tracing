#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "Vector3.h"

enum Refl_t{DIFF, SPEC, REFR};

class Object{
public:
	Object();
	virtual ~Object();
	
	virtual bool hit(Ray &r)=0; // returns 0 if nohit

	virtual Vector3 get_color()=0;
	virtual Refl_t get_refl()=0;
	virtual Vector3 get_emi()=0;

protected:
	Vector3 c; // color
	Refl_t refl; // reflection type (DIFFuse, SPECular, REFRactive)
	Vector3 e; // emission	
};

#endif
