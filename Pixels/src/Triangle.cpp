#include "Triangle.h"

float close(float f){
	if(f >= -0.001)
		return fabs(f);
	return f;
}


Triangle::Triangle(){
	Vec2d p = {0,0};
	pt.push_back(p);
	pt.push_back(p);
	pt.push_back(p);
}


Triangle::Triangle(Vec2d a,Vec2d b,Vec2d c){
	pt.push_back(a);
	pt.push_back(b);
	pt.push_back(c);
}

bool Triangle::inside(Vec2d p){
	float u,v,w;
	barycentric(p,&u,&v,&w);
	return u >= 0 && v >= 0 && w >= 0;
}


void Triangle::barycentric(Vec2d p,float* u,float* v,float *w){
	Vec2d v0 = pt[1]-pt[0];
	Vec2d v1 = pt[1]-p;
	Vec2d v2 = pt[2]-p;
	//area of the big triangle
	float abc = v0.cross(pt[2]-pt[0])/2;

	//area of two smaller triangles
	float pbc = v1.cross(pt[2]-p)/2;
	float pca = v2.cross(pt[0]-p)/2;

	*u = close(pbc/abc);
	*v = close(pca/abc);
	*w = close(1.0f-*v-*u);
}

Vec2d Triangle::textureCoord(Vec2d p){
	//float u,v,w;
	//barycentric(p,&u,&v,&w);
	//return uv[0]*u + uv[1]*v + uv[2]*w;
	return p;
}

