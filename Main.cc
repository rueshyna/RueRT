#include "RayTrace.h"
#include<iostream>
#include<vector>
#include <cstdio>
#include <fstream>
#include <string>

using std::cout; 
using std::endl;
using std::vector;
using std::string;
int main(){
  int WIDTH = 300;
  int HEIGHT = 300;
  Color bgColor(0.3,0.5,1);
  //init ray0 and init eye
  Vector3D r0(-1.0, -1.0, -1.0);
  Point eye(5.0,5.0,5.0);

  //init matrix
  Matrix matrix;
  matrix.setInitRay(&r0);
  
  vector<Object> objects;
  
  //light point
  Point light_point(20, -10, 20);
  Color light_color(0.6,0.6,0.6);
  Object light(&light_point, 1, &light_color,1);
  objects.push_back(light);
  
  //circle
  Point circle_center(0,0,0);
  Color circle_color(1.0,0.0,0.0);
  Object circle(&circle_center,8.0 , &circle_color,0);
  objects.push_back(circle);

  //viewport
  vector< Pixel > image;
  
  for(int i=0; i!= WIDTH; ++i){
    for(int j=0; j!= HEIGHT; ++j){
      Pixel pixel;

      /* uv to xyz convert
       * return eye to screen vector
       */
      Vector3D ray = matrix.computVector(i,j,500,500,WIDTH,HEIGHT,75.0);
      ray.normalize();
      pixel.ray = ray;
      
      int step(1);
      pixel.color=pixel.rayTrace(&ray, &eye, &step, &bgColor, &objects);
      image.push_back(pixel);
    }
  }
  
  std::ofstream outfile;
  
  outfile.open("raytrace.ppm",std::ofstream::out);
  outfile <<"P3\n"<< WIDTH<<" "<< HEIGHT <<"\n"<< 255 <<"\n";

  double r, g, b;
   
  for (vector<Object>::size_type j = 0; j < image.size(); ++j) {
    r = (image[j].color.getR()>1)?1:image[j].color.getR();
    g = (image[j].color.getG()>1)?1:image[j].color.getG();
    b = (image[j].color.getB()>1)?1:image[j].color.getB();
    outfile << floor(r*255)<<" "<< floor(g*255) <<" "<< floor(b*255) << "\n";
  }
  outfile.close();

  return 0;
};
