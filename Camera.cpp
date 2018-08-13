#include "Camera.h"
#include <omp.h>

Camera::Camera(int _w, int _h, int _samples, Scene* _scene)
	: w(_w), h(_h), samples(_samples), scene(_scene)
{
	p = Vector3(_scene->d/2.0,_scene->d/2.0,_scene->d*3.2);
	d = Vector3(0,0,-1).norm();
	pixel_buffer = new float[w*h*3];
}
	
Camera::~Camera(){}

void Camera::render(){
	Vector3 cx = Vector3(w*.5/h,0,0);
	Vector3 cy = (cx.cross(d)).norm()*.5;
	Vector3 r;

#pragma omp parallel for schedule(dynamic, 1) private(r) // OpenMP
	for (int y=0; y<h; y++){ // Loop over image rows
		fprintf(stderr,"\rRendering (%d x %d, %d samples per pixel) %5.2f%%", w, h, samples,100.*y/(h-1));
		for (int x=0; x<w; x++){   // Loop cols
			r = Vector3();
			for (int s=0; s<samples; s++){
				double r1=2*rand1(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
				double r2=2*rand1(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
				Vector3 dir = cx*( ( (1.0 + dx)/2 + x)/w - .5) +
                    cy*( ( (1.0 + dy)/2 + y)/h - .5) + d;
				
				Ray ray(p+dir*140, dir.norm());
				r = r + scene->trace(ray,0)*(1./samples);
			}
			int i=(h-1-y)*w+x;
			pixel_buffer[i*3]   = clamp((float)r.x);
			pixel_buffer[i*3+1] = clamp((float)r.y);
			pixel_buffer[i*3+2] = clamp((float)r.z);
		}
	}
}

void Camera::output_to_file(){
	FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
	for (int i=0; i<w*h*3; i++)
		fprintf(f,"%d ", float_to_int(pixel_buffer[i]));

	fclose(f);
}