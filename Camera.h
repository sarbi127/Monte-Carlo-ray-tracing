#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Scene.h"
#include <stdlib.h>

class Camera{
public:
	Camera(int _w, int _h, int _samples, Scene* _scene);
	~Camera();

	Vector3 p;
	Vector3 d;
	float* pixel_buffer;

	void render();
	void output_to_file();

private:
	int w;
	int h;
	int samples;

	Scene* scene;
	
	inline float rand1(){ return rand() / (RAND_MAX + 1.0f);}

	inline float clamp(float x){ return x<0 ? 0 : x>1 ? 1 : x; }
	inline int float_to_int(float x){ return int(pow(clamp(x),1/2.2)*255+.5); }
};

#endif
