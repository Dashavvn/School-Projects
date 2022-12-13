#ifndef SVG__H
#define SVG__H
#include "Vec2d.h"
#include "Image.h"
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

struct SVG{
	int strokeSize;
    vector<string> cmds;
	Color fillColor;
	SVG(int width, int height);
	void drawLine(Vec2d a, Vec2d b);
	void fillCircle(Vec2d c, float radius);
	void end();
	void write(string filename);
};



#endif
