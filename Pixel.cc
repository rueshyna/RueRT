#include "RayTrace.h"

Pixel::Pixel(){}

Color Pixel::rayTrace(Vector3D *v,Point *p,
                       const int *step,Color *bgColor,vector<Object> *objects){
  Color local, reflected, transmitted;
  Vector3D n;
  int max(1);
  double t;
  double minDist(10E10);
  int intersectDot = -1;

  if(max > *step){
    return *bgColor;
  }

  for(vector<Object>::size_type i = 0; i != objects->size(); ++i){
    t = (*objects)[i].rayIntersection(v,p);
    if(t < minDist){
      minDist = t;
      intersectDot=i;
    }
  }

  if(intersectDot == -1){
    return *bgColor;
  }
  
  Vector3D nn((*v).getX()-(*objects)[intersectDot].center.getX(),(*v).getX()-(*objects)[intersectDot].center.getY(),v->getZ()-(*objects)[intersectDot].center.getZ());
  n=nn;
  n.normalize();
  
  double vDotr(0-v->getX()+2*(v->getX()*n.getX())*n.getX()+0-v->getY()+2*(v->getY()*n.getY())*n.getY()+0-v->getX()+2*(v->getZ()*n.getZ())*n.getZ()); 
  
  if(0 < vDotr){
    Color c(0.5*0.2*pow(vDotr,2),0.8*0.2*pow(vDotr,2),0.8*0.2*pow(vDotr,2));
    local = c;
  }else{
    Color c(50*0.2*pow(0,2),50*0.2*pow(0,2),50*0.2*pow(0,2));
    local = c;
  }

  return local;
}
