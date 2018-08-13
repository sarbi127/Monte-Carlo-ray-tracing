#include "Cube.h"

Cube::~Cube(){}

Cube::Cube(Vector3 o, double d){
	Vector3 v0(0,0,0);
	Vector3 v1(0,d,0);
	Vector3 v2(d,d,0);
	Vector3 v3(d,0,0);
	Vector3 v4(0,0,d);
	Vector3 v5(0,d,d);
	Vector3 v6(d,d,d);
	Vector3 v7(d,0,d);

	v0+=o;
	v1+=o;
	v2+=o;
	v3+=o;
	v4+=o;
	v5+=o;
	v6+=o;
	v7+=o;

	Rectangle* w1 = new Rectangle(v5,v4,v0,v1, Vector3(), Vector3(.9,.9,.1), DIFF); // left
	Rectangle* w2 = new Rectangle(v2,v6,v5,v1, Vector3(), Vector3(.9,.9,.1), DIFF); // top
	Rectangle* w3 = new Rectangle(v3,v7,v6,v2, Vector3(), Vector3(.9,.9,.1), DIFF); // right
	Rectangle* w4 = new Rectangle(v4,v7,v3,v0, Vector3(), Vector3(.9,.9,.1), DIFF); // bottom
	Rectangle* w5 = new Rectangle(v3,v2,v1,v0, Vector3(), Vector3(.9,.9,.1), DIFF); // back
	Rectangle* w6 = new Rectangle(v4,v5,v6,v7, Vector3(), Vector3(.9,.9,.1), DIFF); // front

	faces.push_back(w1);
	faces.push_back(w2);
	faces.push_back(w3);
	faces.push_back(w4);
	faces.push_back(w5);
	faces.push_back(w6);
}

bool Cube::hit(Ray &r){
	bool hit_face;
	bool ret = false;
	
	for(unsigned int i=0; i<faces.size(); i++){
		hit_face = faces[i]->hit(r);
		if(hit_face){
			id = i;
			ret = true;
		}
	}

	return ret;
}