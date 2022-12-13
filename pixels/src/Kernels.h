#ifndef KERNELS__H
#define KERNELS__H
#include "Image.h"
#include <iostream>

Image* convolution(Image* src, Image* kernel);

Image* gaussianKernel();
Image* boxKernel(int size);
Image* sobelVertical();
Image* sobelHorizontal();
Image* edgeDetection(Image* src);
#endif
