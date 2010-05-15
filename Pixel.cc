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
  double t;
  double minDist(10E10);
  int intersectDot = -1;

  if(*step > 1){
    return *bgColor;
  }

  for(vector<Object>::size_type i = 0; i != objects->size(); ++i){
    t = (*objects)[i].rayIntersection(ray,p);
    if(t < minDist && !(*objects)[i].isLight){
      minDist = t;
      intersectDot=i;
    }
  }
  
  if(t < 0){
    return *bgColor;
  }else{
    Vector3D l;
    int light;
    
    Vector3D hitRay = ray->multiplication(&t);
    Point hitPoint = p->addVector(&hitRay);

    for(vector<Object>::size_type i=0; i!=objects->size(); ++i){
      if((*objects)[i].isLight){
        Vector3D ll = (*objects)[i].center - hitPoint;
        l = ll;
	l.normalize();
	light = i;
      }
    }
    
    Vector3D n = hitPoint-(*objects)[intersectDot].center;
    n.normalize();

    Color Ia(0.5,0.3,0.1);
    Color Ka(0.3,0.3,0.3);
    Color ambient=Ia * Ka;

    Color Ip = (*objects)[intersectDot].color;
    Color Kd(0.9,0.8,0.8);
    double rd(this->max(0,(n.Dot(&l))));
    Color diffuse = Ip*(Kd.multiplication(&rd));

    double twoNDotL(2*n.Dot(&l));
    Vector3D r(n.multiplication(&twoNDotL) - l);

    Vector3D zero(0,0,0);
    Vector3D v = zero - (*ray);

    Color Ks(0.4,0.4,0.4);
    double rs(pow(max(0,r.Dot(&v)),32));
    Color specular = Ip * Ks.multiplication(&rs);

    return ambient + diffuse + specular;
  }

 /* if(t > 0){
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
    double nDotL(l.getX()*n.getX()+l.getY()*n.getY()+l.getZ()*n.getZ());

    Vector3D r(-(l.getX())+2*(nDotL)*n.getX(),
               -(l.getY())+2*(nDotL)*n.getY(),
               -(l.getZ())+2*(nDotL)*n.getZ());
    r.normalize();

    Vector3D v(0-ray->getX(),0-ray->getY(),0-ray->getZ());
    v.normalize();
  
    double diff_max(this->max(0,n.getX()*l.getX()+n.getY()*l.getY()+n.getZ()*l.getZ()));
  
    Color diffuse((*objects)[intersectDot].color.getR()
                      *(0.9+(*objects)[ilight].color.getR()*diff_max),
                  (*objects)[intersectDot].color.getG()
		      *(0.2+(*objects)[ilight].color.getG()*diff_max),
                  (*objects)[intersectDot].color.getB()
                     *(0.2+(*objects)[ilight].color.getB()*diff_max));
    
    double phong_max(this->max(0,v.getX()*r.getX()+v.getY()*r.getY()+v.getZ()*r.getZ()));
    Color phong((*objects)[ilight].color.getR()*
                  (*objects)[intersectDot].color.getR()*pow(phong_max,128),
                (*objects)[ilight].color.getG()*
	          (*objects)[intersectDot].color.getG()*pow(phong_max,128),
	        (*objects)[ilight].color.getB()*
                  (*objects)[intersectDot].color.getB()*pow(phong_max,128));
  
    Color lo(diffuse.getR()+phong.getR(),
             diffuse.getG()+phong.getG(),
             diffuse.getB()+phong.getB());
    return lo;
  }else{
    return *bgColor;
  }*/
}

