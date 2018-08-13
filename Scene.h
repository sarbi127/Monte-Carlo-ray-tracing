#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Ray.h"
#include <stdlib.h>
#include <vector>
using namespace std;

const float PI=3.14159265358979f;

class Scene{
public:
	Scene(double _d); // size of the box
	~Scene();
	
	Vector3 trace(Ray &r, int depth);
	
	double d;

private:
	vector<Object *> objects;

	bool hit(Ray &r, int &id);
		
	inline float rand1(){ return rand() / (RAND_MAX + 1.0f);}
	
};

#endif
