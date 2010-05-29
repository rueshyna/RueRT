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
  int WIDTH = 1000;
  int HEIGHT = 1000;
  Color bgColor(0.3,0.5,1);
  //init ray0 and init eye
  Point r_c(0.0,0.0,0.0);
  Point eye(0.0,1000.0,0.0);
  Vector3D r0 = r_c-eye;
  double distence(sqrt(pow(r0.getX(),2)+pow(r0.getY(),2)+pow(r0.getZ(),2)));
  r0.normalize();

  srand(time(NULL));

  //init matrix
  Matrix matrix;
  matrix.setInitRay(&r0);

  vector<Object> objects;

  //light point
  Point light_point(200, 100, 200);
  Color light_color(1.0,1.0,1.0);
  Object light(&light_point, 1, &light_color,1);
  objects.push_back(light);

  //light point
  /*Point light_point2(-400, 500, 200);
  Color light_color2(1.0,1.0,1.0);
  Object light2(&light_point2, 1, &light_color2,1);
  objects.push_back(light2);*/

  //circle1
  Point circle_center(600,-200,-600);
  Color circle_color(0.9,0.9,0.2);
  Object circle(&circle_center,600.0 , &circle_color,0);
  objects.push_back(circle);

  //circle2
  Point circle_center2(-100,-20,100);
  Color circle_color2(0.5,0.9,0.6);
  Object circle2(&circle_center2,50.0,&circle_color2,0);
  objects.push_back(circle2);

  //circle3
  Point circle_center3(100,-550,100);
  Color circle_color3(0.5,0.6,0.9);
  Object circle3(&circle_center3,300.0,&circle_color3,0);
  objects.push_back(circle3);

  //viewport
  vector< Pixel > image;

  for(int j=0; j!= HEIGHT; ++j){
    for(int i=0; i!= WIDTH; ++i){
      Pixel pixel;

      /* uv to xyz convert
       * return eye to screen vector
       */
      Vector3D ray = matrix.computVector(i,j,WIDTH,HEIGHT,WIDTH,HEIGHT,distence);
      int step(1);
      pixel.color=pixel.rayTrace(&ray, &eye, &step, &bgColor, &objects, -1);
      image.push_back(pixel);
    }
  }

   std::ofstream outfile;

  outfile.open("raytrace.ppm",std::ofstream::out);
  outfile <<"P3\n"<< WIDTH<<" "<< HEIGHT <<"\n"<< 255 <<"\n";

  double r, g, b;

  for (vector<Object>::size_type j = 0; j < image.size(); ++j) {
    r = image[j].color.getR();
    g = image[j].color.getG();
    b = image[j].color.getB();
    outfile << floor(r*255)<<" "<< floor(g*255) <<" "<< floor(b*255) << "\n";
  }
  outfile.close();

  return 0;
};
