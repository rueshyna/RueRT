#include "RayTrace.h"
#include<iostream>
#include<vector>
#include <cstdio>
using std::cout;
using std::endl;
using std::vector;

int main(){
  int WEIGHT = 300;
  int HIGHT = 300;
  Color bgColor(0.3,0.5,1);
  //init ray0 and init eye
  Vector3D r0(-1.0, -1.0, -1.0);
  Point eye(5.0,5.0,5.0);
//  r0.normalize(); 
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
  
  
  for(int i=0; i!= WEIGHT; ++i){
    for(int j=0; j!= HIGHT; ++j){
      Pixel pixel;

      //uv to xyz
      Point screen = matrix.computVector(i,j,500,500,WEIGHT,HIGHT,75.0,&eye);
      
      //light ray
      Vector3D ray(screen.getX()-eye.getX(),screen.getY()-eye.getY(),screen.getZ()-eye.getZ());
      ray.normalize();
      pixel.ray = ray;
      int step(1);
      pixel.color=pixel.rayTrace(&ray, &eye, &step, &bgColor, &objects);
	 //cout << pixel.color.getR()<<" "<< pixel.color.getG()<<" " << pixel.color.getB()<<endl;
      image.push_back(pixel);
    }
  }
  FILE *fp;
  fp = fopen("./raytrace.ppm", "w");
  if (fp != NULL) {
   fprintf(fp, "%s\n", "P6");
   fprintf(fp, "%d %d\n", WEIGHT, HIGHT);
   fprintf(fp, "%d\n", 255);
   double r, g, b;
   
   
   for (int j = 0; j < image.size(); ++j) {

   //r = (image[j].color.getR()>1)?1:image[j].color.getR();
   //g = (image[j].color.getG()>1)?1:image[j].color.getG();
   //b = (image[j].color.getB()>1)?1:image[j].color.getB();
   
   fprintf(fp, "%c%c%c", (int)(image[j].color.getR()*255), ((int)image[j].color.getG()*255), (int)(image[j].color.getB()*255));
     //      fprintf(fp, "%c%c%c", (int)(r*255), (int)(g*255), (int)(b*255));
   }
   fclose(fp);
}

  return 0;
};
