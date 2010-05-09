#include "Object.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

int main(){
  int WEIGHT = 100;
  int HIGHT = 100;
  Vector3D r0(1.0, 1.0, 1.0);
  Point eye(0.0,0.0,0.0);
  Matrix matrix;
  matrix.setInitRay(&r0);

  Point light(100,100,100);

  Point circle_center(50,50,50);
  Color circle_color(10,20,30);
  Object circle(&circle_center,20 , &circle_color);
  
  vector< vector<Pixel> > image;
Point ppp;
  for(int i=-(WEIGHT/2); i != WEIGHT/2; ++i){
    for(int j=HIGHT/2; j!= -(HIGHT/2); --j){
      Point screen_p = matrix.computVector(i,j,WEIGHT,HIGHT,WEIGHT,HIGHT,4.0,&eye);
      ppp = circle.rayIntersection(&screen_p,&eye);
      cout << i<<" "<< j<<" "<< ppp.getX() << " " << ppp.getY() << " "<< ppp.getZ() << endl;
    }
  }
  
  return 0;
};
