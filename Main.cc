#include "RayTrace.h"
#include<iostream>
#include<vector>
#include <cstdio>
using std::cout;
using std::endl;
using std::vector;

int main(){
  int WEIGHT = 100;
  int HIGHT = 100;
  Color bgColor(255,255,255);
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
  Point circle_center(100,100,100);
  Color circle_color(10,20,30);
  Object circle(&circle_center,20 , &circle_color,0);
  objects.push_back(circle);

  //viewport
  vector< Pixel > image;
  
  
  for(int i=-(WEIGHT/2); i != WEIGHT/2; ++i){
    for(int j=HIGHT/2; j!= -(HIGHT/2); --j){
      Pixel pixel;

      //uv to xyz
      Point screen = matrix.computVector(i,j,WEIGHT,HIGHT,WEIGHT,HIGHT,10.0,&eye);
      
      //light ray
      Vector3D ray(eye.getX()-screen.getZ(),eye.getY()-screen.getY(),eye.getZ()-screen.getZ());
      ray.normalize();
      pixel.ray = ray;
      int step(1);
      pixel.color=pixel.rayTrace(&ray, &eye, &step, &bgColor, &objects);
      image.push_back(pixel);
	 cout << pixel.color.getR()<<" "<< pixel.color.getG()<<" " << pixel.color.getB()<<endl;
    }
  }

  FILE *fp;
  fp = fopen("./raytrace.ppm", "w");
  if (fp != NULL) {
	  fprintf(fp, "%s\n", "P6");
	  fprintf(fp, "%d %d\n", WEIGHT, HIGHT);
	  fprintf(fp, "%d\n", 255);
	  char r, g, b;
	  float gamma = 1; // mac
	  for (int j = 0; j < HIGHT; ++j) {
		  for (int i = 0; i < WEIGHT; ++i) {
 //			  image[j*HIGHT+i].pixel.color.getR() //= 255 * powf(pixels[i][j].r, gamma);
			  //pixels[i][j].g = 255 * powf(pixels[i][j].g, gamma);
			  //pixels[i][j].b = 255 * powf(pixels[i][j].b, gamma);
			  //r = (pixels[i][j].r > 255) ? 255 : pixels[i][j].r;
			  //g = (pixels[i][j].g > 255) ? 255 : pixels[i][j].g;
			  //b = (pixels[i][j].b > 255) ? 255 : pixels[i][j].b;
			  fprintf(fp, "%c%c%c", (int)image[j*HIGHT+i].color.getR(), (int)image[j*HIGHT+i].color.getG(), (int)image[j*HIGHT+i].color.getB());
	 //cout << (int)image[j*HIGHT+i].color.getR()<<" "<< (int)image[j*HIGHT+i].color.getG()<<" " << (int)image[j*HIGHT+i].color.getB()<<endl;
		  }
		 // fprintf(fp, "\n");
	  }
	  fclose(fp);
}

  return 0;
};
