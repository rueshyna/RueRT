#include "RayTrace.h"
   
double Object::rayIntersection(Vector3D *_ray, Point *p){
   Vector3D ray = *_ray; 
   
   double t;
   double a(1);
   double b(2*(ray.getX()*(center.getX()-(*p).getX())+ray.getY()*(center.getY()-(*p).getY())+ray.getZ()*(center.getZ()-(*p).getZ())));
   double c(pow(center.getX()-(*p).getX(),2)+pow(center.getY()-(*p).getY(),2)+pow(center.getZ()-(*p).getZ(),2)-pow(r,2));
   double d((pow(b,2)-4*a*c));

   if(d < 0){
     t=NAN;
     return t;
   }
   
   double t0((-b-sqrt(d))/2);

   if(d = 0){
     t = t0; 
     return t;
   }
   
   if(t0 <= 0){
     double t1((-b+sqrt(d))/2);
     
     if(t1 <= 0){
       return NAN;
     }else{
       t = t1;
     }
   }else{
     t=t0;
   }
   
   return t;
 }

Object::Object(Point *p, double rr, Color *c, int isl):r(rr), islight(isl){
  center = *p;
  color = *c;
}
