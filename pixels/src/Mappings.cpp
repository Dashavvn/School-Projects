#include "Mappings.h"

void ZoomMap::transform(float& u, float&v){
	u = u*width+x;
	v = v*height+y;
}

void RotateMap::transform(float& u, float&v){
	float s = sqrt(2);
	float r = 0.5;
	float x = (u-r)*2;
	float y = (v-r)*2;

	float theta = rotateTheta;

	x *= s;
	y *= s;

	u = x*cos(theta) - y*sin(theta);
	v = x*sin(theta) + y*cos(theta);

	u = (u/2)+r;
	v = (v/2)+r;
}


void ScaleMap::transform(float& u, float&v){

}

//Analytical Methods for Squaring the Disc
//Chamberlain Fong
void SphereMap::transform(float& u, float& v){
	float x = 2*(u) - 1;
	float y = 2*(v) - 1;

	float a = sqrt(2+(x*x) - (y*y) + 2*sqrt(2)*x)/2 - sqrt(2+x*x - y*y - 2*sqrt(2)*x)/2;
	float b = sqrt(2-(x*x) + (y*y) + 2*sqrt(2)*y)/2 - sqrt(2-x*x + y*y - 2*sqrt(2)*y)/2;

	u = (a+1)/2;
	v = (b+1)/2;
}

void SwirlMap::transform(float& u, float& v){
	double PI = 4*atan(1);
	float x = u-0.5;
	float y = v-0.5;
	float r = sqrt(x*x + y*y);
	float theta = PI*r;
	u = (x)*cos(theta) + (y)*sin(theta) + 0.5;
	v = -(x)*sin(theta) + (y)*cos(theta) + 0.5;
}

void WaveMap::transform(float& u,float &v){
	double PI = 4*atan(1);
	//0.05 is size, 3 is number of waves
	float y = v+sin(2*PI*(u)*3)*0.05;
	v = y;
}

void FlipMap::transform(float& u, float& v){
	u = 1-u;
}

//magic! -- figure out what I did
void RingMap::transform(float& u, float& v){
	float x = (u-0.5)*2;
	float y = (v-0.5)*2;
	float d = sqrt(x*x+y*y);
	if(d < 0.3){
		u = 0;
		v = 0;
	}else if(d < 1){
		x /= d;
		y /= d;

		float p = (d-0.3)/0.7;

		u =(x*p);
		v = (y*p);

		u = (u/2)+0.5;
		v = (v/2)+0.5;

	}
	SphereMap s;
	s.transform(u,v);
}



