#include "RayTrace.h"

double Pixel::max(double a, double b){
  return (a>b)?a:b;
}

Pixel::Pixel(){}

Color Pixel::rayTrace(Vector3D *ray,Point *p,
                       const int *step,Color *bgColor,vector<Object> *objects){
  Color local, reflected, transmitted;
  Vector3D l;
  Vector3D n;
  int max(1);
  double t;
  double minDist(10E10);
  int intersectDot = -1;

  if(max < *step){
    return *bgColor;
  }
  //Color c(1,1,0);
  for(vector<Object>::size_type i = 0; i != objects->size(); ++i){
    t = (*objects)[i].rayIntersection(ray,p);
    if(t < minDist){
      minDist = t;
      intersectDot=i;
    }
  }
// cout << this->color.getR()<<" "<< this->color.getG()<<" " << this->color.getB()<<endl;
//cout << t << endl;
  if(t > 0){
  //  cout << "hit" <<endl; 
     local = (*objects)[intersectDot].color;
     return local;
  }else{
    //cout << "back " << bgColor->getR()<<endl; 
    return *bgColor;
  }
/*
  Vector3D nn(ray->getX()-(*objects)[intersectDot].center.getX(),
              ray->getX()-(*objects)[intersectDot].center.getY(),
	      ray->getZ()-(*objects)[intersectDot].center.getZ());
  n=nn;
  n.normalize();
  
  for(vector<Object>::iterator iter=objects->begin(); iter!=objects->end(); ++iter){
   if(iter->isLight == 1){
     Vector3D ll(iter->center.getX()-(*objects)[intersectDot].center.getX(),
                iter->center.getY()-(*objects)[intersectDot].center.getY(),
	        iter->center.getZ()-(*objects)[intersectDot].center.getZ());
     ll.normalize();
     l=ll;
    }
  }


  double vDotr(0-ray->getX()+2*(ray->getX()*n.getX())*n.getX()+
               0-ray->getY()+2*(ray->getY()*n.getY())*n.getY()+
	       0-ray->getX()+2*(ray->getZ()*n.getZ())*n.getZ()); 
  
  Color diffuse(0.8*(0.2+(*objects)[intersectDot].center.getX()*this->max(0,n.getX()+l.getX())),
                0.8*(0.2+(*objects)[intersectDot].center.getY()*this->max(0,n.getX()+l.getY())),
                0.8*(0.2+(*objects)[intersectDot].center.getZ()*this->max(0,n.getX()+l.getZ())));
  Color phong(0.2*(*objects)[intersectDot].center.getX()*pow(this->max(0,vDotr),2),
              0.2*(*objects)[intersectDot].center.getX()*pow(this->max(0,vDotr),2),
	      0.2*(*objects)[intersectDot].center.getX()*pow(this->max(0,vDotr),2));

  Color lo(diffuse.getR()+phong.getR(),
              diffuse.getG()+phong.getG(),
              diffuse.getG()+phong.getB());
  return lo;*/
}

