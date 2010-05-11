#include "RayTrace.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

int main(){
  int WEIGHT = 100;
  int HIGHT = 100;
  
  //init ray0 and init eye
  Vector3D r0(1.0, 1.0, 1.0);
  Point eye(0.0,0.0,0.0);
  
  //init matrix
  Matrix matrix;
  matrix.setInitRay(&r0);
  
  vector<Object> objects;
  
  //light point
  Point light_point(100,100,100);
  Color light_color(0,0,0);
  Object light(&light_point, 1, &light_color,1);
  objects.push_back(light);
  
  //circle
  Point circle_center(50,50,50);
  Color circle_color(10,20,30);
  Object circle(&circle_center,20 , &circle_color,0);
  objects.push_back(circle);

  //viewport
  vector< Pixel > image;
  
  
  for(int i=-(WEIGHT/2); i != WEIGHT/2; ++i){
    for(int j=HIGHT/2; j!= -(HIGHT/2); --j){
      Pixel pixel;
      image.push_back(pixel);
      

      //uv to xyz
      Point screen = matrix.computVector(i,j,WEIGHT,HIGHT,WEIGHT,HIGHT,4.0,&eye);
      
      //light ray
      Vector3D ray(eye.getX()-screen.getZ(),eye.getY()-screen.getY(),eye.getZ()-screen.getZ());
      ray.normalize();
      pixel.ray = ray;
      
      //pixel.color=colorTracy() 
      
    }
  }
  
  return 0;
};
