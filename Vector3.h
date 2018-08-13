#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

class Vector3{
public:
	Vector3();
	Vector3(double _x, double _y, double _z);
	~Vector3();


	double x, y, z;


	Vector3 operator+(const Vector3 &b) const { 
		return Vector3(x+b.x,y+b.y,z+b.z); 
	}
	
	Vector3 operator-(const Vector3 &b) const { 
		return Vector3(x-b.x,y-b.y,z-b.z); 
	}
  
	Vector3 operator*(double b) const { 
		return Vector3(x*b,y*b,z*b); 
	}
  
	Vector3 mult(const Vector3 &b) const { 
		return Vector3(x*b.x,y*b.y,z*b.z); 
	}
  
	Vector3& norm(){ 
		return *this = *this * (1/sqrt(x*x+y*y+z*z)); 
	}
  
	double dot(const Vector3 &b) const { 
		return x*b.x+y*b.y+z*b.z; 
	} 
  
	/*
	Vector3 operator%(Vector3&b){
		return Vector3(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);
	}
	*/
	
	inline Vector3 cross(const Vector3 &b) const{
		return Vector3(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);
	}

	bool operator == (const Vector3 &v) const{
		if(x != v.x) return false;
		if(y != v.y) return false;
		if(z != v.z) return false;
		return true;
	}

	inline Vector3 &operator += (const Vector3 &p){
		x += p.x; y += p.y; z += p.z;
		return *this;
	}
};

#endif
