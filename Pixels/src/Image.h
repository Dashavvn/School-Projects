#ifndef IMAGE__H
#define IMAGE__H

#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include "Utility.h"
#include "Mappings.h"

using namespace std;

struct Color{
	int red,green,blue,alpha;
};

struct Image{
	int height;
	int width;
	int channels;
	unsigned char* data;

	Color getColor(int x,int y);
	Color getColorSigned(int x, int y);
	void setColor(Color c,int x,int y);
	void fillAlpha(int alpha);//should add alpha if not there
	void removeAlpha();
	void clear();

	Color getSample(float u,float v);
	void setSample(Color c,float u,float v);

	template <typename T>
	void backwardMap(Image* src,T f){
	    for(int y =0; y < height; ++y){
		    for(int x=0; x < width; ++x){
		        float u = (float)x/(float)(width-1);
			    float v = (float)y/(float)(height-1);
			    f.transform(u,v);
				setColor(src->getSample(u,v),x,y);
			}
		}
	}


	~Image();
	Image(int w,int h,int c);
};

Color colorToGrey(Color p);
float colorDistance(Color p, Color q);
Color colorPyth(Color a,Color b);
Color operator*(Color c,int a);
Color operator*(Color c,float a);
Color operator*(Color a,Color b);
Color operator/(Color a,Color b);
Color operator/(Color a,int b);
Color operator+(Color a,Color b);
Color operator-(Color a,Color b);


void toGreyscale(Image* img);


string colorToString(Color c);


#endif
