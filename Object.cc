#include "RayTrace.h"
   
#include <fstream>
double Object::rayIntersection(Vector3D *ray, Point *p){
   Vector3D p_a((*p)-center);
   double t(-2);
   double a(ray->dot(ray));
   double b(p_a.dot(ray));
   double c(p_a.dot(&p_a)-r*r);
   double d(b*b-a*c);

    //cout<<p_a.getX() << " "<<p_a.getY() <<" " <<p_a.getZ()<<endl;
    //cout<<center.getX() << " "<<center.getY() <<" " <<center.getZ()<<endl;
   if(d < 0.0){
     t=-1;
    //cout<<"t a b c d" <<t << " "<<a <<" "<< b<<" "<<c<<" "<<d<<endl;
     return t;
   }
   
   double t0(-b-sqrt(d));

   if(d == 0.0){
     t = (t0>0)?t0:-1; 
    //cout<<"bbb \n" <<t<<endl;
     return t;
   }
   
   if(d>0.0){ 
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
    //cout<<"ccc \n" <<t<<endl;
     return t;
   }
    //cout<<"ddd \n" <<t<<endl;
   return t;
 }

Object::Object(Point *p, double rr, Color *c, int isL):r(rr), isLight(isL){
  center = *p;
  color = *c;
}
