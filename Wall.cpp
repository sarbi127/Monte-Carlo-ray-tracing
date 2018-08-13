#include "Wall.h"

Wall::Wall(double d){
	Vector3 v0(0,0,0);
	Vector3 v1(0,d,0);
	Vector3 v2(d,d,0);
	Vector3 v3(d,0,0);
	
	Vector3 v4(0,0,2*d);
	Vector3 v5(0,d,2*d);
	Vector3 v6(d,d,2*d);
	Vector3 v7(d,0,2*d);

	Rectangle* w1 = new Rectangle(v1,v0,v4,v5, Vector3(), Vector3(.9,.1,.1), DIFF); // left
	Rectangle* w2 = new Rectangle(v1,v5,v6,v2, Vector3(), Vector3(.9,.9,.9), DIFF); // top
	Rectangle* w3 = new Rectangle(v2,v6,v7,v3, Vector3(), Vector3(.1,.1,.9), DIFF); // right
	Rectangle* w4 = new Rectangle(v0,v3,v7,v4, Vector3(), Vector3(.5,.5,.5), DIFF); // bottom
	Rectangle* w5 = new Rectangle(v0,v1,v2,v3, Vector3(), Vector3(.9,.9,.9), DIFF); // back
	
	faces.push_back(w1);
	faces.push_back(w2);
	faces.push_back(w3);
	faces.push_back(w4);
	faces.push_back(w5);
}

Wall::~Wall(){}


bool Wall::hit(Ray &r){
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