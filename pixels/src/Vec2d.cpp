#include "Vec2d.h"

float Vec2d::cross(Vec2d b){
	return b.x*y-b.y*x;
}

Vec2d operator+(Vec2d a,Vec2d b){
	return {a.x+b.x,a.y+b.y};
}

Vec2d operator-(Vec2d a,Vec2d b){
	return {a.x-b.x,a.y-b.y};
}

Vec2d operator*(Vec2d a,float f){
	return {a.x*f,a.y*f};
}

Vec2d operator/(Vec2d a,float f){
	return {a.x/f,a.y/f};
}

Vec2d Vec2d::rotate(float theta){
	return {x*(float)cos(theta)-y*(float)sin(theta),x*(float)sin(theta)+y*(float)cos(theta)};
}

void Vec2d::square(){
	x = x*x;
	y = y*y;
}

float Vec2d::distance(Vec2d b){
    return sqrt(x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);
}


