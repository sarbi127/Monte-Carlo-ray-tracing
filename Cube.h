#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
#include "Rectangle.h"
#include <vector>
using namespace std;

class Cube : public Object
{
public:
	Cube(Vector3 o, double d);
	~Cube();

	bool hit(Ray &r);

	inline Vector3 get_color(){ 
		return faces[id]->get_color();
	};

	inline Refl_t get_refl(){ 
		return faces[id]->get_refl();
	};

	inline Vector3 get_emi(){ 
		return faces[id]->get_emi();
	};

private:
	vector<Rectangle *> faces;
	int id;
};

#endif
