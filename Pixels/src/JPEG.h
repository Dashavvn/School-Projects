#ifndef JPEG__H
#define JPEG__H

#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include "Image.h"

//magic!
Image* readJpeg(const char* filename);
void writeJpeg(const char* filename,Image* image, int quality);

#endif
