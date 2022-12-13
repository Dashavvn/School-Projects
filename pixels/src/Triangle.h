#ifndef TRIANGLE__H
#define TRIANGLE__H

#include "Vec2d.h"
#include <vector>
#include <cmath>
using namespace std;

struct Triangle{
    vector<Vec2d> pt;
    Triangle();
    Triangle(Vec2d a,Vec2d b,Vec2d c);
    void barycentric(Vec2d p,float* u,float* v,float *w);
    bool inside(Vec2d p);
    Vec2d textureCoord(Vec2d p);
};


#endif
