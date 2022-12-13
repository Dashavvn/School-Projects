#include <iostream>
#include "Image.h"
#include "PNG.h"
#include "JPEG.h"
#include "Kernels.h"
#include "Quantization.h"
#include "Dither.h"
#include "Mappings.h"
#include "Drawing.h"
#include "Font.h"
#include "Triangle.h"
using namespace std;

/*int main(){
	Image* img = new Image(300,300,4);
	RegularPolygon p({100,100},42,75);
	Color green = {175,0,125};
	p.draw(img,green);
	img->fillAlpha(255);
	writePng("polygon.png",img);
	delete img;
	return 0;
}*/


int main(){
	Triangle t({50,50},{250,225},{275,0});
	Image* img = new Image(300,300,4);

	shadeTriangle(img,t);

	img->fillAlpha(255);
	writePng("triangle.png",img);
	delete img;
	return 0;
}

/*int main(){
	Image* img = new Image(300,300,4);
	HersheyFont font;
	font.load("hershey-fonts/gothgbt.jhf");
	font.scale(2);
	Color green = {33,150,0};

	font.draw("Ai0E",img,{10,100},green);
	img->fillAlpha(255);
	writePng("font.png",img);
	delete img;
	return 0;

}*/


/*int main(){
	Image* img = readPng("cs.png");
	Image* zoom = new Image(300,300,4);
	ZoomMap s = {0.2f,0.2f,0.2f,0.2f};

	zoom->backwardMap(img,s);

	zoom->fillAlpha(255);
	writePng("zoom.png",zoom);
	delete zoom;
	delete img;
	return 0;
}*/


/*int main(){
	Color green = {33,150,0};
	Color red = {150,33,0};

	Image* img = new Image(100,100,4);

	Line one = {{40,80},{80,32}};
	one.draw(img,green);
	Line two = {{80,32},{40,50}};
	two.draw(img,red);

	img->fillAlpha(255);
	writePng("draw.png",img);
	delete img;

	return 0;
}*/



int olderTest(){
	Color r = {233,9,0};
	Image* img = readPng("cs.png");
//	toGreyscale(img);
	Image* result;
/*	Image* blur = gaussianKernel();
	for(int i =0; i < 10; ++i){
		result = convolution(img,blur);
		delete img;
		img = result;
	}
	delete blur;
*/

/*	Image* box = boxKernel(3); 
	result = convolution(img,box);
	delete img;
	delete box;
	img = result;
	result = edgeDetection(img);
	delete img;
*/

/*	result = medianCutPallet(img,1024);
	result->fillAlpha(255);
	floydSteinberg(img,result);
	writePng("file.png",img);
*/

//	SphereMap s;
//	SwirlMap s;
//	RingMap s;
//	WaveMap s;
//	FlipMap s;
//	ScaleMap s;
	float PI = 4*atan(1);
	RotateMap s = {PI/3.0f};

	result = new Image(img->width,img->height,img->channels);
	result->backwardMap(img,s);
	result->fillAlpha(255);
	writePng("map.png",result);
	delete result;


	

	return 0;
}
