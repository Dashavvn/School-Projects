#include "Drawing.h"
#include <cmath>

RegularPolygon::RegularPolygon(Vec2d center, int sides, float size){
  for(int i =0; i < sides; ++i){
    pts.push_back({center.x+sin((float)M_PI*2/sides*i)*size,center.y+cos((float)M_PI*2/sides*i)*size});
  }
}

void RegularPolygon::draw(Image* img, Color c){
  for(int i =0; i < pts.size(); ++i){
    //Line l = {pts[i],pts[(i+1)%pts.size()]};
    //l.draw(img,c);
   ((Line){pts[i],pts[(i+1)%pts.size()]}).draw(img,c);
  }
}


void Line::draw(Image* dest, Color c){
  float dx = (int)b.x-(int)a.x;
  float dy = (int)b.y-(int)a.y;
  float d = sqrt(dx*dx + dy*dy);
  float p = (int)b.x*(int)a.y-(int)b.y*(int)a.x;
  for(int y = fmin(a.y,b.y); y <= fmax(a.y,b.y); ++y){
    for(int x = fmin(a.x,b.x); x <= fmax(a.x,b.x); ++x){
      float dist = fabs(dy*x-dx*y+p)/d;
      if(dist <= 1){
        Color p = dest->getColor(x,y);
        p = lerp(dist,c,p);
        dest->setColor(p,x,y);
      }
    }
  }
}

void fillTriangle(Image* dest, Triangle t, Color c){
  float minX = fmin(t.pt[0].x,fmin(t.pt[1].x,t.pt[2].x));
  float minY = fmin(t.pt[0].y,fmin(t.pt[1].y,t.pt[2].y));
  float maxX = fmax(t.pt[0].x,fmax(t.pt[1].x,t.pt[2].x));
  float maxY = fmax(t.pt[0].y,fmax(t.pt[1].y,t.pt[2].y));
  for(int y = minY; y <= maxY; ++y){
    for(int x = minX; x <= maxX; ++x){
      if(t.inside({(float)x,(float)y})){
        dest->setColor(c,x,y);
      }
    }
  }
  Line one = {t.pt[0],t.pt[1]};
  Line two= {t.pt[1],t.pt[2]};
  Line three= {t.pt[2],t.pt[0]};
  one.draw(dest,c);
  two.draw(dest,c);
  three.draw(dest,c);
}

void shadeTriangle(Image* dest, Triangle t){
  Color a = {220,0,220};
  Color b = {220,120,0};
  Color c = {0,0,220};
  float minX = fmin(t.pt[0].x,fmin(t.pt[1].x,t.pt[2].x));
  float minY = fmin(t.pt[0].y,fmin(t.pt[1].y,t.pt[2].y));
  float maxX = fmax(t.pt[0].x,fmax(t.pt[1].x,t.pt[2].x));
  float maxY = fmax(t.pt[0].y,fmax(t.pt[1].y,t.pt[2].y));
  for(int y = minY; y <= maxY; ++y){
    for(int x = minX; x <= maxX; ++x){
      if(t.inside({(float)x,(float)y})){
        float u,v,w;
        t.barycentric({(float)x,(float)y},&u,&v,&w);
        Color k = a*u + b*v + c*w;

        dest->setColor(k,x,y);
      }
    }
  }

}
