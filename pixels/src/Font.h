#ifndef FONT__H
#define FONT__H
#include <vector>
#include <fstream>
#include "Drawing.h"
using namespace std;

struct HersheySymbol{
    vector<vector<Vec2d>> lines;
    int left, right;
    void parse(string line);
    void draw(Image* img, Vec2d center, Color c);
    void scale(float f);
};

struct HersheyFont{
    vector<HersheySymbol> symbols;
    void load(string filename);
    void scale(float f);
    void draw(string text,Image* img, Vec2d center, Color c);

};

#endif
