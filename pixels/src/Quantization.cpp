#include "Quantization.h"

struct colorcompare {
	bool operator() (const Color& lhs, const Color& rhs) const{
		return colorToGrey(lhs).red < colorToGrey(rhs).red;
	}
};


Image* medianCutPallet(Image* src, int count){
	set<Color,colorcompare> colorSet;	

	for(int y = 0; y < src->height; ++y){
		for(int x = 0; x < src->width; ++x){
			colorSet.insert(src->getColor(x,y));
		}
	}
	vector<Color> pallet(colorSet.begin(),colorSet.end());


	int i =0;
	while(pallet.size() > count){
		pallet[i] = (pallet[i]+pallet[i+1])/2;
		pallet.erase(pallet.begin()+i+1);
		i = (i+1)% pallet.size();
	}

	Image* rv = new Image(pallet.size(),1,4);
	for(i =0; i < pallet.size(); ++i){
		rv->setColor(pallet[i],i,0);
	}

	return rv;
}



