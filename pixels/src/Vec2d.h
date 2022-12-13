#ifndef VEC2D__H
#define VEC2D__H
#include <cmath>

struct Vec2d{
	float x,y;
	float cross(Vec2d b);
	void square();
	Vec2d rotate(float theta);
	float distance(Vec2d b);
};

Vec2d operator+(Vec2d a,Vec2d b);
Vec2d operator-(Vec2d a,Vec2d b);
Vec2d operator*(Vec2d a,float f);
Vec2d operator/(Vec2d a,float f);

#endif
