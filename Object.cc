#include "RayTrace.h"
   
#include <fstream>
double Object::rayIntersection(Vector3D *ray, Point *p){
   Vector3D p_a((*p)-center);
   double t(-1);
   double a(ray->dot(ray));
   double b(p_a.dot(ray));
   //double b((ray->getX()*(p->getX()-center.getX())
   //           +ray->getY()*(p->getY()-center.getY())
	//      +ray->getZ()*(p->getZ()-center.getZ())));
   //double c(pow(p->getX()-center.getX(),2.0)+
   //         pow(p->getY()-center.getY(),2.0)+
//	    pow(p->getZ()-center.getZ(),2.0)-
//pow(r,2.0));
   double c(p_a.dot(&p_a)-r*r);
   double d(b*b-a*c);

   if(d < 0){
     t=-1;
     return t;
   }
   
   double t0(-b-sqrt(d));

   if(d == 0){
     t = (t0>0)?t0:-1; 
     return t;
   }
   
   if(d>0){ 
     double t1(-b+sqrt(d));
     if(t0 <= 0){
       if(t1 <= 0){
         t = -1;
       }else{
         t = t1;
       }
     }else{
       t=t0;
     }
   }
   return t;
 }

Object::Object(Point *p, double rr, Color *c, int isL):r(rr), isLight(isL){
  center = *p;
  color = *c;
}
