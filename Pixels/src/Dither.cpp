#include "Dither.h"

int indexOfClosestColor(Color p, Image* pallet){
	float dist = 0;
	int index = -1;
	for(int i = 0; i < pallet->width; ++i){
		Color q = pallet->getColor(i,0);
		float d = colorDistance(p,q);
		if(index == -1 || d < dist){
			index = i;
			dist = d;
		}
	}
	return index;
}

void floydSteinberg(Image* image,Image* pallet){
	Color p,q;
	//for each pixel
	for(int y =0; y < image->height; ++y){
		for(int x =0; x < image->width; ++x){
			//finded the closest pallet color
			p = image->getColor(x,y);
			q = pallet->getColor(indexOfClosestColor(p,pallet),0);

			//find the error
			Color error = p-q;;

			image->setColor(q,x,y);

			//distribute error to the surrounding pixels
			image->setColor(error*(7.0f/16.0f)+image->getColor(x+1,y  ),x+1,y);
            image->setColor(error*(3.0f/16.0f)+image->getColor(x-1,y+1),x-1,y+1);
            image->setColor(error*(5.0f/16.0f)+image->getColor(x  ,y+1),x  ,y+1);
            image->setColor(error*(1.0f/16.0f)+image->getColor(x+1,y+1),x+1,y+1);

		}
	}
}
