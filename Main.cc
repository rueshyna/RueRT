#include "RayTrace.h"

int main(){
  Color bgColor(0.2,0.2,0.2);
  Noise noise;
  noise.initHashTable();

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

  Vector3D lightAreaV(-1,0,0);
  Matrix lightArea;
  lightArea.setInitRay(&lightAreaV);

  //light point
  for(int i=0; i < 2; i++){
    for(int j=0; j < 2; j++){
      Vector3D l_point = lightArea.computVector(i,j,150,150,2,2,500);

      Point light_point(l_point.getX()+100.0, l_point.getY()*100.0+500.0, l_point.getZ()*100.0+0.0);
      Color light_color(1.0,1.0,1.0);
      Object light(&light_point, 1, &light_color,1,LIGHT, &noise);
      objects.push_back(light);
    }
  }

  //circle1
  Point circle_center(600,-200,-600);
  Color circle_color(0.9,0.9,0.2);
  Object circle(&circle_center,600.0 , &circle_color,0, FIRE,&noise);
  objects.push_back(circle);

  //circle2
  Point circle_center2(10,-20,10);
  Color circle_color2(0.7,0.5,0.2);
  Object circle2(&circle_center2,100.0,&circle_color2,0, WOOD, &noise);
  objects.push_back(circle2);

  //circle3
  Point circle_center3(100,-550,100);
  Color circle_color3(0.5,0.62,0.78);
  Object circle3(&circle_center3,300.0,&circle_color3,0,CLOUD, &noise);
  objects.push_back(circle3);

  //viewport
  vector< Pixel > image;

  for(int j=0; j!= HEIGHT; ++j){
    for(int i=0; i!= WIDTH; ++i){
      Pixel pixel;

      /* uv to xyz convert
       * return eye to screen vector
       */
      Vector3D ray = matrix.computVector(i,j,1000,1000,WIDTH,HEIGHT,distence);
      int step(1);
      pixel.color=pixel.rayTrace(&ray, &eye, &step, &bgColor, &objects, -1);
      image.push_back(pixel);
    }
  }

  IO::save("raytrace.ppm",&image);

  return 0;
};
