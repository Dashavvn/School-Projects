#ifndef MAPPINGS_H
#define MAPPINGS_H
#include <cmath>
using namespace std;


struct SphereMap{
	void transform(float& u, float& v);
};

struct SwirlMap{
    void transform(float& u, float& v);
};

struct WaveMap{
    void transform(float& u, float& v);
};

struct RingMap{
    void transform(float& u, float& v);
};

struct FlipMap{
    void transform(float& u, float& v);
};

struct ScaleMap{
	void transform(float& u, float&v);
};

struct RotateMap{
    void transform(float& u, float& v);
	float rotateTheta;
};

struct ZoomMap{
    void transform(float& u, float& v);
    float x,y,width,height;
};

#endif 
