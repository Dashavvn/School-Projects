#include "Image.h"

Color colorToGrey(Color p){
	float avgf = ((float)p.red)*0.3 + ((float)p.green)*0.6 + ((float)p.blue)*0.11;
	p.red = p.green = p.blue = max(0,min((int)avgf,255));
	return p;
}

string colorToString(Color c){
	return "{" + to_string(c.red) + "," + to_string(c.green) + "," + to_string(c.blue) +  "," + to_string(c.alpha) +"}";
}

Color colorPyth(Color a,Color b){
	a = a*a+b*b;
	return {(int)sqrt(a.red),(int)sqrt(a.green),(int)sqrt(a.blue),(int)sqrt(a.alpha)};
}


float colorDistance(Color p, Color q){
	Color r = p-q;
	r = r*r;
	return sqrt(r.red+r.green+r.blue);
}

Color operator*(Color c,float a){
    return {(int)(c.red*a),(int)(c.green*a),(int)(c.blue*a),(int)(c.alpha*a)};
}

Color operator*(Color c,int a){
	return {c.red*a,c.green*a,c.blue*a,c.alpha*a};
}

Color operator*(Color a,Color b){
	return {a.red*b.red, a.green*b.green, a.blue*b.blue,a.alpha*b.alpha};
}

Color operator/(Color a,Color b){
	Color c = {0,0,0,0};
	c.red   = (b.red != 0 ? a.red/b.red : a.red);
	c.green = (b.green != 0 ? a.green/b.green : a.green);
	c.blue  = (b.blue != 0 ? a.blue/b.blue : a.blue);
	c.alpha = (b.alpha != 0 ? a.alpha/b.alpha : a.alpha);
	return c;
}

Color operator/(Color a,int b){
	return b != 0 ? (Color){a.red/b,a.green/b,a.blue/b,a.alpha/b} : a;
}

Color operator+(Color a,Color b){
	return {a.red+b.red, a.green+b.green, a.blue+b.blue,a.alpha+b.alpha};
}

Color operator-(Color a,Color b){
    return {a.red-b.red, a.green-b.green, a.blue-b.blue,a.alpha-b.alpha};
}

void Image::fillAlpha(int alpha){
    for(int y =0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            Color c = getColor(x,y);
			c.alpha = max(0,min(alpha,255));
            setColor(c,x,y);
        }
    }
}



void toGreyscale(Image* img){
	for(int y =0; y < img->height; ++y){
		for(int x = 0; x < img->width; ++x){
			Color c = img->getColor(x,y);
			float avgf = ((float)c.red)*0.3 + ((float)c.green)*0.6 + ((float)c.blue)*0.11;
			c.red = c.green = c.blue = max(0,min((int)avgf,255));
			img->setColor(c,x,y);
		}
	}
}


Color Image::getColor(int x,int y){
	Color c = {0,0,0,0};
	if(x >= 0 && x < width && y >= 0 && y < height){
		unsigned char* color = &data[(y*width+x)*channels];
		c.red   = max(0,min((int)color[0],255));
		c.green = max(0,min((int)color[1],255));
		c.blue  = max(0,min((int)color[2],255));
		if(channels == 4){
			c.alpha = max(0,min((int)color[3],255));
		}
	}
	return c;
}


Color Image::getColorSigned(int x,int y){
	Color c = {0,0,0,0};
	if(x >= 0 && x < width && y >= 0 && y < height){
		unsigned char* color = &data[(y*width+x)*channels];
		c.red   = max(0,min((int)color[0],255));
		c.green = max(0,min((int)color[1],255));
		c.blue  = max(0,min((int)color[2],255));
		if(channels == 4){
			c.alpha = max(0,min((int)color[3],255));
		}
	}
	if(c.alpha != 0){
		c = c*-1;
		c.alpha = 0;
	}
	return c;
}

void Image::setColor(Color c,int x,int y){
	if(x >= 0 && x < width && y >= 0 && y < height){
		unsigned char* color = &data[(y*width+x)*channels];
		color[0] = (unsigned char)max(0,min(abs(c.red),255));
		color[1] = (unsigned char)max(0,min(abs(c.green),255));
		color[2] = (unsigned char)max(0,min(abs(c.blue),255));
		if(channels == 4){
			color[3] = (unsigned char)max(0,min(abs(c.alpha),255));
		}
	}
}

Color Image::getSample(float u,float v){
	float fx = (width-1)*u;
	float fy = (height-1)*v;
	int x = fx;
	int y = fy;
	return lerp(fy-y,
			lerp(fx-x,getColor(x,y),getColor(x+1,y)),
			lerp(fx-x,getColor(x,y+1),getColor(x+1,y+1)));

}


void Image::removeAlpha(){
	if(channels != 4)
		return;
	unsigned char* into = new unsigned char[width*height*3];
	unsigned char* loop = into;
	for(int i =0; i < width*height*4; ++i){
		if(i%4 != 3){
			*loop = data[i];
			loop++;
		}
	}
	delete data;
	data = into;
	channels = 3;
}

Image::Image(int w, int h,int c){
	width = w;
	height = h;
	channels = c;
	data = new unsigned char[w*h*channels];
	memset(data,0,w*h*channels);
}

void Image::clear(){
	memset(data,0,width*height*channels);
}


Image::~Image(){
	delete data;
}
