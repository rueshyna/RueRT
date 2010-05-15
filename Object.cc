#include "RayTrace.h"
   
double Object::rayIntersection(Vector3D *ray, Point *p){
   double t;
   double a(1);
   double b(2.0*(ray->getX()*(p->getX()-center.getX())
              +ray->getY()*(p->getY()-center.getY())
	      +ray->getZ()*(p->getZ()-center.getZ())));
   double c(pow(p->getX()-center.getX(),2.0)+
            pow(p->getY()-center.getY(),2.0)+
	    pow(p->getZ()-center.getZ(),2.0)-
	    pow(r,2.0));
   double d((pow(b,2.0)-4.0*a*c));

   if(d < 0){
     t=-1;
     return t;
   }
   
   double t0((-b-sqrt(d))/2.0);

   if(d == 0){
     t = t0; 
     return t;
   }
   
   if(t0 <= 0){
     double t1((-b+sqrt(d))/2.0);
     
     if(t1 <= 0){
       t = -1;
     }else{
       t = t0;
     }
   }else{
     t=t0;
   }
   return t;
 }

Object::Object(Point *p, double rr, Color *c, int isL):r(rr), isLight(isL){
  center = *p;
  color = *c;
}
