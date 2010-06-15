#include "RayTrace.h"

int main(){
  Color bgColor(0.7,0.7,0.7);
  Noise noise;
  noise.initHashTable();

  //init ray0 and init eye
  Point r_c(0.0,0.0,0.0);
  Point eye(0.0,1000.0,0.0);
  Vector3D r0 = r_c-eye;
  double distence(sqrt(pow(r0.getX(),2)+pow(r0.getY(),2)+pow(r0.getZ(),2)));
  r0.normalize();

  vector<Point> f_eye;
  Point f_eye1(-0.025,1000.0,-0.001);
  f_eye.push_back(f_eye1);
  Point f_eye2(-0.01,1000.0,0.002);
  f_eye.push_back(f_eye2);
  Point f_eye4(-0.035,1000.0,0.001);
  f_eye.push_back(f_eye4);
  f_eye.push_back(eye);

  srand(time(NULL));

  //init matrix
  Matrix matrix;
  matrix.setInitRay(&r0);

  vector<Object> objects;

  Vector3D lightAreaV(-1,0,0);
  Matrix lightArea;
  lightArea.setInitRay(&lightAreaV);

  //focus plan
  Point p_focus(-200,-300,170);
  Color c_focus(0.7,0.3,0.7);
  Object focus_plan(&p_focus,150.0,&c_focus,0,LIGHT, &noise);

  //light point
  for(int i=0; i < 2; i++){
    for(int j=0; j < 2; j++){
      Vector3D l_point = lightArea.computVector(i,j,150,150,2,2,500);

      Point light_point(l_point.getX()+0.0, l_point.getY()*50.0-400.0, l_point.getZ()*100.0+400.0);
      Color light_color(1.0,1.0,1.0);
      Object light(&light_point, 1, &light_color,1,LIGHT, &noise);
      objects.push_back(light);
    }
  }

  Point light_point1(0, 400, 100);
  Color light_color1(1.0,1.0,1.0);
  Object light1(&light_point1, 1, &light_color1,1,LIGHT, &noise);
  objects.push_back(light1);

  Point light_point2(100, 400, 100);
  Color light_color2(1.0,1.0,1.0);
  Object light2(&light_point2, 1, &light_color2,1,LIGHT, &noise);
  objects.push_back(light2);

  //circle1
  IO io_read1;
  vector<Color> cImage1=io_read1.readPicture("sun.ppm");
  Point circle_center(0,-100,-1000);
  Color circle_color(0.9,0.9,0.2);
  Object circle(&circle_center,800.0 , &circle_color,0, CYLINDER,&noise, &cImage1);
  objects.push_back(circle);
  //circle2
  Point circle_center2(800,-1800,790);
  Color circle_color2(0.9,0.6,0.0);
  Object circle2(&circle_center2,150.0,&circle_color2,0, WOOD, &noise);
  objects.push_back(circle2);

  //circle3
  Point circle_center3(600,-1500,570);
  Color circle_color3(0.5,0.62,0.78);
  Object circle3(&circle_center3,150.0,&circle_color3,0,CLOUD, &noise);
  objects.push_back(circle3);

  //circle4
  Point circle_center4(400,-1200,360);
  Color circle_color4(0.7,0.3,0.7);
  Object circle4(&circle_center4,150.0,&circle_color4,0,MARBLE, &noise);
  objects.push_back(circle4);

  //circle5
  IO io_read;
  vector<Color> cImage=io_read.readPicture("earth.ppm");
  Point circle_center5(-200,-300,170);
  Color circle_color5(0.7,0.3,0.7);
  Object circle5(&circle_center5,150.0,&circle_color5,0,GLOBE, &noise, &cImage);
  objects.push_back(circle5);

  //circle6
  Point circle_center6(0,-600,0);
  Color circle_color6(0.7,0.9,0.7);
  Object circle6(&circle_center6,150.0,&circle_color6,0,SINE, &noise);
  objects.push_back(circle6);

  //circle7
  Point circle_center7(200,-900,150);
  Color circle_color7(0.7,0.9,0.7);
  Object circle7(&circle_center7,150.0,&circle_color7,0,FIRE, &noise);
  objects.push_back(circle7);

  //circle8
  IO io_read2;
  vector<Color> cImage2=io_read2.readPicture("background.ppm");
  Point circle_center8(-400,0,400);
  Color circle_color8(0.7,0.9,0.7);
  Object circle8(&circle_center8,150.0,&circle_color8,0,PLANAR, &noise, &cImage2);
  objects.push_back(circle8);
  
  //viewport
  vector< Pixel > image;

  for(int j=0; j!= HEIGHT; ++j){
    for(int i=0; i!= WIDTH; ++i){
      Pixel pixel;

/*     uv to xyz convert
 *      return eye to screen vector
 */
      Vector3D ray = matrix.computVector(i,j,1000,1000,WIDTH,HEIGHT,distence);
      Point focus_p(ray.getX()+eye.getX(), ray.getY()+eye.getY(), ray.getZ()+eye.getZ());
      vector<Vector3D> focus_v;

      for(vector<Point>::iterator iter=f_eye.begin(); iter!=f_eye.end(); ++iter){
        Vector3D fpp=focus_p-(*iter);
        focus_v.push_back(fpp);
      }

      int step(1);
      Color totalC(0.0,0.0,0.0);
      int count(0);
      int hasInsect = (focus_plan.rayIntersection(&focus_v[focus_v.size()-1],
                      &f_eye[f_eye.size()-1]) == -1)? 0:1;
      if(hasInsect){
        totalC= totalC+pixel.rayTrace(&focus_v[focus_v.size()-1],
                                      &f_eye[f_eye.size()-1], step, &bgColor, &objects, -1);
       count += 1;
      }else{
        for(int i=0 ; i!=focus_v.size(); ++i){
          int otherInsect = (focus_plan.rayIntersection(
                                    &focus_v[i], &f_eye[i]) == -1)? 0:1;
          if(!otherInsect){
            totalC= totalC+pixel.rayTrace(&focus_v[i], &f_eye[i], step, &bgColor, &objects,-1);
            count+=1;
          }
        }
      }


      Color avgC(totalC.getR()/count,
                 totalC.getG()/count,
                 totalC.getB()/count);
      pixel.color = avgC;
      image.push_back(pixel);
    }
  }

  IO::save("raytrace.ppm",&image);
  return 0;
};
