#ifndef WALL_H
#define WALL_H

#include "Object.h"
#include "Rectangle.h"
#include <vector>
using namespace std;


class Wall : public Object
{
public:
	Wall(double d);
	~Wall();

	bool hit(Ray &r);

	inline Vector3 get_color(){ return faces[id]->get_color();};
	inline Refl_t get_refl(){ return faces[id]->get_refl();};
	inline Vector3 get_emi(){ return faces[id]->get_emi();};

private:
	vector<Rectangle *> faces;
	int id;
};

#endif
