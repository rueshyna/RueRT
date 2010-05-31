#include "RayTrace.h"
   
#include <fstream>
double Object::rayIntersection(Vector3D *ray, Point *p){
   Vector3D p_a((*p)-center);
   double t(-2);
   double a(ray->dot(ray));
   double b(p_a.dot(ray));
   double c(p_a.dot(&p_a)-r*r);
   double d(b*b-a*c);

   if(d < 0.0){
     t=-1;
     return t;
   }

   double t0(-b-sqrt(d));

   if(d == 0.0){
     t = (t0>0)?t0:-1; 
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
     return t;
   }
   return t;
 }

Object::Object(Point *p, double rr, Color *c, int isL, MATERIAL_TYPE m):r(rr), isLight(isL), material(m){
  center = *p;
  color = *c;
}

Color Object::materialColor(Point *p){
  switch(material){
  case LIGHT :
    break;
  case WOOD :
    break;
  case FIRE :
    break;
  case CLOUD :
    break;
  case MARBLE :
    break;
  case SINE:
    return ssin(p);
  default :
    return color;
  }
}

Color Object::wood_material(Point *p){
  return color;
}

Color Object::ssin(Point *p){
  Color c0(0.0,0.5,0.0);
  double t((1.0+sin(p->getX()*3.14159265/100.0))/2.0);
  double t_(1.0-t);
  return c0.multiplication(&t_)+color.multiplication(&t);
}
