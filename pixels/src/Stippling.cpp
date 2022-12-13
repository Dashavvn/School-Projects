#include "Stippling.h"

//convert a pixel into an "index"
//	index is a 24 bit integer
int pixelToIndex(Color p){
  int index = ((p.red & 0xFF) << 16) | ((p.green & 0xFF) << 8) | (p.blue & 0xFF);
  return index-1;
}

//convert an index into a Color
//	index should start with 0 BUT we never store a zero index because we add one
//	we only return a -1 when the pixel hasn't had an index stored in it (empty)
Color indexToPixel(int index){
  index += 1;
  Color rv;
  rv.red   = (index >> 16) & 0x00FF;
  rv.green = (index >> 8)  & 0x00FF;
  rv.blue  = (index)       & 0x00FF;
  return rv;
}

//offsets for the neighboring pixels
//	we can scale these offsets to deal with farther pixels
Vec2d offsets[] = {
  {-1.0f,-1.0f},{0.0f,-1.0f},{1.0f,-1.0f},
  {-1.0f, 0.0f},{0.0f, 0.0f},{1.0f, 0.0f},
  {-1.0f, 1.0f},{0.0f, 1.0f},{1.0f, 1.0f}
};


struct VoronoiRegion{
  float density;
  Vec2d total;
  Vec2d squared;
  float mixed;
  float area;

  VoronoiRegion(){
    area = 0;
    density = 0;
    total = {0,0};
    squared = {0,0};
    mixed = 0;
  }


  //add a sample to the density function
  //	x,y -- are the location
  //	value -- will be how far the color is from white (black == 1)
  void addSample(float x,float y,float value){
    area += 1;
    density += value;
    Vec2d c = {x,y};
    total = total + (c*value);
    c.square();
    squared = squared + (c*value);
    mixed += x*y *value;
  }

  //return the weighted mean of the region
  Vec2d mean(){
    Vec2d rv = {0,0};
    if(area != 0){
      rv = total / density;
    }
    return rv;
  }

  //return the angle of the largest spread
  float angle(){
    Vec2d m = mean();
    //cov(x,y) = 1/n * sum( (x-m.x) * (y-m.y))
    //Cov(x,x)
    float x = squared.x/density - (m.x*m.x);
    float y = squared.y/density - (m.y*m.y);
    float xy = mixed/density - m.x*m.y;
    return atan2(2*xy,x-y)/2.0;
  }

};




//your work begins!
//	a function to calculate the nearest seed point in the voronoi diagram
//	seed points are stored as indices (don't ask) to Vec2ds in the points vector
//	img -- is where the indices are stored
//	loc -- is the pixel we are currently working on
//	distance -- how far out we want to look
//	points -- the vector of seed points

Color nearest(Image* img, Vec2d loc,float distance,vector<Vec2d>& points){
  Color s = {0,0,0};
  int small = -1;
  //for each offset
  for(int i = 0; i < 9;++i){
    Vec2d p = loc + offsets[i] * distance;
    //make sure that loc + offset is in bounds
    if(p.x >= 0 && p.y >= 0 && p.x < img->width && p.y < img->height){ 
      // get the pixel
      int ndx = pixelToIndex(img->getColor(p.x, p.y));
      //make sure pixel is storing a valid index

      //calculate the distance to the seed point at the index
      //if the distance is smaller
      if(ndx > -1){
	if(small == -1 || loc.distance(points[ndx]) < loc.distance(points[small])){
	  //save the pixel
	  small = ndx;
	  s = indexToPixel(small);	
	}
      }		
    }
  }
  //return the index to the seed with the smallest distance
  return s;
}




//The jump flood algorithm
//	img -- the image that will store the nearest seed point index for each location
//	points -- the seed points
void jumpFlood(Image* img,vector<Vec2d>& points){
  vector<int> steps;
  //calculate the lg_2 number of distances
  //	make sure you start with the larger of width/2 or height/2
  //	first number in vector should be 1 then max(width/2, height/2)
  steps.push_back(1);
  int s = max(img->width, img->height)/2;
  while(s>=1)
  {
    steps.push_back(s);
    s/=2;
  }
  for(int times = 0; times < steps.size(); ++times){
    //for each pixel	  
    for(int y =0; y < img->height; ++y)
    {
      for(int x = 0; x < img->width; ++x)
      {
	//set the pixel to the nearest point
	Vec2d loc = {float(x), float(y)};
	img->setColor(nearest(img,loc,steps[times],points),x,y);
      }
    }
  }
}




//The weighted voronoi stippling code
//returns a list of points which will be used as seeds
//regions -- the voronoi regions
vector<Vec2d> wv(vector<VoronoiRegion>& regions){
  vector<Vec2d> centers;
  //for each regions
  for(VoronoiRegion r: regions){
    //get the mean
    centers.push_back(r.mean());
  }
  return centers;
}





//The lbg voronoi stippling code
//returns a list of points which will be used as seeds
//regions -- the voronoi regions
//alpha -- the parameter to split on
vector<Vec2d> lbg(vector<VoronoiRegion>& regions,float alpha){
  float radius = 2;
  float area = M_PI * radius * radius;
  vector<Vec2d> centers;
  float lower = (1.0f - alpha /2.0f) * area;
  float upper = (1.0f + alpha /2.0f) * area;
  //for each region
  for(VoronoiRegion r : regions)
  {
    if (r.area < 3)
    {
    } 
    else if (r.density >= lower and r.density <= upper)
      {
	centers.push_back(r.mean());
      }
      else if(r.density > upper)
      {
	r.angle();//use angle func then pushback answer
	  //centers.push_back();
	  //centers.push_back();
      }
      //if the region is too small ignore
      //else if the density is between upper and lower
      //just put the mean back
      //else if density is above upper
      //split!
      //this should be split along the major axis of the density function
      //two Vec2ds should be added
    }
  
    return centers;
  }






//The big function
//takes in a number of points, iterations, and an Image
//the image should be gray scale
//returns a vector of Vec2ds... this would need to change to have dynamic sizes
vector<Vec2d> stippling(Image* img,int points,int iterations){
  vector<Vec2d> centers;
  //randomly create some number of seed points
  //i have been starting with 1000
  for(int i =0; i < points; ++i)
  {
    centers.push_back({(float)(rand()%img->width), (float)(rand()%img->height)});
  }

  //create an image to store the voronoi
  Image* voronoi = new Image(img->width,img->height,4);
  for(int times = 0; times < iterations; ++times){
    printf("lloyds %d\n",times);
    vector<VoronoiRegion>regions(centers.size());
    voronoi->clear();
    //for the centers
    for(int i = 0; i < centers.size(); ++i)
    {
      voronoi->setColor(indexToPixel(i),centers[i].x,centers[i].y);
    }
    //set the pixels in the voronio image to the index of the center
    jumpFlood(voronoi,centers);
    //for each pixel
    //add the x,y and color sample to the appropriate region
    for(int y =0; y < voronoi->height; ++y)
    {
      for(int x = 0; x < voronoi->width; ++x)
      {
	Color c = img->getColor(x,y);
	//index to a center!!
	int index = pixelToIndex(voronoi->getColor(x,y));
	if(index != -1){
	  regions[index].addSample(x,y,1-((float)(c.red))/255.0f);
	}    
      }
    }

    //get the next seed points using lgb or wv

    centers = wv(regions);
  }

  delete voronoi;
  //you might want to debug some stuff in here! like export some images or something

  return centers;
}
