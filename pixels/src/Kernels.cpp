#include "Kernels.h"

Image* convolution(Image* src, Image* kernel){
	Image* dest = new Image(src->width,src->height,src->channels);

	for(int y = 0; y < src->height; ++y){
		for(int x = 0; x < src->width; ++x){
			Color c = {0,0,0};
			Color sum = {0,0,0};
			for(int j = -(kernel->height/2); j <= kernel->height/2; ++j){
				for(int i = -(kernel->width/2); i <= kernel->width/2; ++i){
					if(x+i >= 0 && x+i < src->width && y+j >= 0 && y+j < src->height){
						Color k = kernel->getColorSigned(i+kernel->width/2,j+kernel->height/2);
						Color n = src->getColor(x+i,y+j);
						c = c+(k*n);
					
//						cout << colorToString(c) << endl;
						sum = sum+k;
					}
				}
			}
			c = c/sum;
			dest->setColor(c,x,y);
		}
	}
	return dest;
}

Image* boxKernel(int size){
	size -= (size+1)%2;
	Image* box = new Image(size,size,3);
	for(int y = 0; y < size;++y){
		for(int x = 0; x < size; ++x){
			box->setColor({1,1,1},x,y);
		}
	}
	return box;
}

Image* gaussianKernel(){
	Image* dest = new Image(3,3,3);
	dest->setColor({32,32,32},1,1);
	
	dest->setColor({16,16,16},0,1);
    dest->setColor({16,16,16},1,0);
    dest->setColor({16,16,16},2,1);
    dest->setColor({16,16,16},1,2);
    
	dest->setColor({8,8,8},0,0);
    dest->setColor({8,8,8},2,0);
    dest->setColor({8,8,8},0,2);
    dest->setColor({8,8,8},2,2);
	return dest;
}

//Sobel edge detection
Image* sobelHorizontal(){
    Image* kernel = new Image(3,3,4);
	kernel->setColor({1,1,1},0,0);	
    kernel->setColor({2,2,2},0,1);
    kernel->setColor({1,1,1},0,2);

    kernel->setColor({1,1,1,255},2,0);
    kernel->setColor({2,2,2,255},2,1);
    kernel->setColor({1,1,1,255},2,2);

    return kernel;
}

//Sobel edge detection
Image* sobelVertical(){
    Image* kernel = new Image(3,3,4);
    kernel->setColor({1,1,1},0,0);
    kernel->setColor({2,2,2},1,0);
    kernel->setColor({1,1,1},2,0);

    kernel->setColor({1,1,1,255},0,2);
    kernel->setColor({2,2,2,255},1,2);
    kernel->setColor({1,1,1,255},2,2);

    return kernel;
}


Image* edgeDetection(Image* src){
	Image* hor = sobelHorizontal();
	Image* ver = sobelVertical();

	Image* alpha = convolution(src,hor);
	Image* beta  = convolution(src,ver);

	for(int y = 0; y < alpha->height; ++y){
		for(int x = 0; x < alpha->width; ++x){
			alpha->setColor(colorPyth(alpha->getColorSigned(x,y),beta->getColorSigned(x,y)),x,y);
		}
	}
	delete hor;
	delete ver;
	delete beta;
	return alpha;
}



