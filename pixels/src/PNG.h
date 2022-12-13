#ifndef PNGIMAGE__H
#define PNGIMAGE__H

#include <stdlib.h>
#include <stdio.h>
#include "Image.h"
#include <png.h>
#include <string.h>
Image* readPng(const char* filename);
void writePng(const char* filename,Image* image);

#endif
