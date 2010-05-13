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
  //   local = (*objects)[intersectDot].color;
   //  return local;
 // }else{
    //cout << "back " << bgColor->getR()<<endl; 

  Vector3D nn(ray->getX()*t+p->getX()-(*objects)[intersectDot].center.getX(),
              ray->getY()*t+p->getY()-(*objects)[intersectDot].center.getY(),
	      ray->getZ()*t+p->getZ()-(*objects)[intersectDot].center.getZ());
  n=nn;
  n.normalize();
  
  
  int ilight;

  for(vector<Object>::size_type i = 0; i!=objects->size(); ++i){
   if((*objects)[i].isLight == 1){
     Vector3D ll((*objects)[i].center.getX()-ray->getX()*t+p->getX(),
                 (*objects)[i].center.getY()-ray->getY()*t+p->getY(),
	         (*objects)[i].center.getZ()-ray->getZ()*t+p->getZ());
     ll.normalize();
     l=ll;
     ilight = i;
    }
  }

  Vector3D r(-(l.getX())+2*(l.getX()*n.getX())*n.getX(),
             -(l.getY())+2*(l.getY()*n.getY())*n.getY(),
             -(l.getZ())+2*(l.getZ()*n.getZ())*n.getZ());
  r.normalize();

  Vector3D v(0-ray->getX(),0-ray->getY(),0-ray->getZ());
  v.normalize();
  
  Color diffuse((*objects)[intersectDot].color.getR()
                    *(0.1+(*objects)[ilight].center.getX()*this->max(0,n.getX()*l.getX())),
                (*objects)[intersectDot].color.getG()
		    *(0.1+(*objects)[ilight].center.getY()*this->max(0,n.getY()*l.getY())),
                (*objects)[intersectDot].color.getB()
		    *(0.1+(*objects)[ilight].center.getZ()*this->max(0,n.getZ()*l.getZ())));

  Color phong((*objects)[ilight].center.getX()*
                (*objects)[intersectDot].center.getX()*pow(this->max(0,v.getX()*r.getX()),2),
              (*objects)[ilight].center.getY()*
	        (*objects)[intersectDot].center.getY()*pow(this->max(0,v.getY()*r.getY()),2),
	      (*objects)[ilight].center.getZ()*
	        (*objects)[intersectDot].center.getZ()*pow(this->max(0,v.getZ()*r.getZ()),2));

  Color lo(diffuse.getR(),
           diffuse.getG(),
           diffuse.getB());
  return lo;
    }else{
    return *bgColor;
  }
}

