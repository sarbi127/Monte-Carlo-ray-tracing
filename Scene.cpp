#include "Scene.h"
#include <time.h>
#include "Sphere.h"
#include "Rectangle.h"
#include "Wall.h"
#include "Cube.h"

Scene::Scene(double _d)
	: d(_d)
{
	Vector3 p0(d/4, d/4, d);
	Sphere* glas = new Sphere(d/8, p0, Vector3(),Vector3(1,1,1)*.999, REFR);

	Vector3 p1(3*d/4, d/2, 2*d/3);
	Sphere* mirr = new Sphere(d/8, p1, Vector3(),Vector3(1,1,1)*.999, SPEC);

	Vector3 o(d/10, d/2, d/10);
	Cube* cube = new Cube(o, d/4);

	Vector3 v0(d/3, d-1, 2*d/3);
	Vector3 v1(d/3, d-1, d);
	Vector3 v2(2*d/3, d-1, d);
	Vector3 v3(2*d/3, d-1, 2*d/3);

	Rectangle* light = new Rectangle(v0, v1, v2, v3, Vector3(12,12,12), Vector3(), DIFF);
	Wall* wall = new Wall(d);

	objects.push_back(wall);
	objects.push_back(light);
	objects.push_back(mirr);
	objects.push_back(glas);
	objects.push_back(cube);

	srand((unsigned int)time(NULL));
}
	
Scene::~Scene(){}

bool Scene::hit(Ray &r, int &id){
	bool hit_obj;
	bool ret = false;
  
	for(unsigned int i=0; i<objects.size(); i++) {
		hit_obj=objects[i]->hit(r);
		if(hit_obj){
			id=i;
			ret=true;
		}
	}
  
	return ret;
}

Vector3 Scene::trace(Ray &r, int depth){
	int id=0; // id of intersected object

	if (!hit(r, id)) 
		return Vector3(); // if miss all objects, return black

	Object* obj = objects[id]; // the hit object

	Vector3 x = r.o + r.d * r.t; // the hitting point
	Vector3 n = r.n; // normal at the hitting point
	Vector3 nl = r.inside ? n*-1 : n; // inside or outside the object

	Vector3 f=obj->get_color();

	if (++depth>10) //if (rand1()<p) f=f*(1/p); else 
		return obj->get_emi(); //R.R.

	if (obj->get_refl() == DIFF){ // DIFFUSE reflection
		double r1=2*PI*rand1();
		double r2=rand1();
		double r2s=sqrt(r2);

		Vector3 w=nl;
		Vector3 u=((fabs(w.x)>.1? Vector3(0,1,0):Vector3(1,0,0)).cross(w)).norm(), v=w.cross(u);
		Vector3 d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
		Ray child(x,d);
		return obj->get_emi() + f.mult(trace(child,depth));
	}
	else if (obj->get_refl() == SPEC){ // SPECULAR reflection
		Ray child(x,r.d-n*2*n.dot(r.d));
		return obj->get_emi() + f.mult(trace(child,depth));
	}

	Ray reflRay(x, r.d-n*2*n.dot(r.d)); // dielectric REFRACTION

	bool into = !r.inside; // Ray from outside going in?

	double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;

	if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0){    // Total internal reflection
		return obj->get_emi() + f.mult(trace(reflRay,depth));
	}

	Vector3 tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();

	double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));

	double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);

	Ray rayx(x,tdir);
	return obj->get_emi() + f.mult(depth>2 ? (rand1()<P ?   // Russian roulette
                                    trace(reflRay,depth)*RP:
                                    trace(rayx,depth)*TP) :
           trace(reflRay,depth)*Re+trace(rayx,depth)*Tr);
}
