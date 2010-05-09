#include "Object.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

int main(){
  int WEIGHT = 50;
  int HIGHT = 50;
  Vector3D r0(1.0, 2.0, 3.0);
  Point eye(1.0,2.0,3.0);
  Matrix matrix;
  matrix.setInitRay(&r0);

  Point light(100,100,100);

  Point circle_center(50,50,50);
  Color circle_color(10,20,30);
  Object circle(&circle_center, 10, &circle_color);
  
  vector< vector<Pixel> > image;

  for(int i=-(WEIGHT/2); i != WEIGHT/2; ++i){
    for(int j=HIGHT/2; j!= -(HIGHT/2); ++j){
      Point screen_p = matrix.computVector(i,j,WEIGHT,HIGHT,WEIGHT,HIGHT,4.0,&eye);
      circle.rayIntersection(&screen_p,&eye);
      cout << i<<" "<< j<<" "<< point.getX() << " " << point.getY() << " "<< point.getZ() << endl;
    }
  }
  
  return 0;
};
