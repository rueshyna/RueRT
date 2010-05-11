#include "RayTrace.h"

Pixel::Pixel(){}

Color* Pixel::rayTrace(const Vector3D *v,const Point *p,
                       const int *step,Color *bgColor,const int self, vector<Object> *object){
  Color local, reflected, transmitted;
  Point q;
  Vector3D n;
  int max(1);

  if(max > *step){
    return bgColor;
  }

  //if(*t != NAN){
    //return 
  //}else{
  //  return bgColor;
  //}

}
