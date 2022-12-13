#include <iostream>
#include "Image.h"
#include "PNG.h"
#include "JPEG.h"
#include "Stippling.h"
#include "SVG.h"
using namespace std;

int main(){
  srand(time(0));

  // open a file save into an image

  Image* img = readPng("picture.png");

  // make the file greyscale

  toGreyscale(img);
  //img->fillAlpha(255);


  // run the stippling function ( stippling(Image* img, int points, int iterations) )

  vector<Vec2d> centers = stippling(img, 1000, 10);

  // write file?

  //create instance of svg struct

  SVG svg(img->width, img->height);

  //draw circles
  for(Vec2d c: centers){
    svg.fillCircle(c, 2);
  }
  svg.end();

  //wwrite svg file

  svg.write("test.svg");

  delete img;
  return 0;
}

