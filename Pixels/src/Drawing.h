#ifndef DRAWING__H
#define DRAWING__H
#include "Vec2d.h"
#include "Image.h"
#include "Triangle.h"
#include <vector>

struct Line{
	Vec2d a;
	Vec2d b;
	void draw(Image* img, Color c);
};

struct RegularPolygon{
	vector<Vec2d> pts;
	RegularPolygon(Vec2d center, int sides, float size);
	void draw(Image* img, Color c);
};

void fillTriangle(Image* dest, Triangle t, Color c);
void shadeTriangle(Image* dest, Triangle t);

#endif
