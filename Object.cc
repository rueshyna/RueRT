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

Object::Object(Point *p, double rr, Color *c, int isL, MATERIAL_TYPE m, Noise *n):r(rr), isLight(isL), material(m){
  center = *p;
  color = *c;
  noise = *n;
}

Color Object::materialColor(Point *p){
  switch(material){
  case LIGHT :
    break;
  case WOOD :
    return wood_material(p);
  case FIRE :
    break;
  case CLOUD :
    break;
  case MARBLE :
    return marble_material(p);
  case SINE:
    return ssin(p);
  default :
    return color;
  }
}

#define PI 3.14159265

Color Object::wood_material(Point *p){
  double radius(sqrt(pow(p->getX(),2.0)+pow(p->getZ(),2.0)));
  double angel(0.0);
  double grain(0.0);

  if(p->getZ()==0){
    angel = 180.0/2.0;
  }else{
    angel = atan2(p->getZ(),p->getX())+180.0;
  }

  radius += 2.0*sin(20.0*angel+p->getY()/150.0);
  //round->floor
  grain = (int)floor(radius)%60;

  if(grain < 40){
    return color;
  }else{
    Color c(0.1,0.2,0.1);
    return c;
  }
}

Color Object::marble_material(Point *p){
  double width(0.02);
  double d,dd;
  double i;

  Point p1(p->getX()/10.0,p->getY()/20.0,p->getZ()/20.0);
  d = (p->getX()+1000.0)*width+7.0*noise.noise_funct(&p1);
  dd = (int)d%17;

  if(dd < 4){
    Point p2(p->getX()/27.0,p->getY()/25.0,p->getZ()/25.0);
    i = 0.7+0.2*noise.noise_funct(&p2);
  }else{
    Point p3(p->getX()/10.0,p->getY()/10.0,p->getZ()/10.0);
    if(dd<9 || dd>=12){
      double temp(d-(d/17)*17.0-10.5);
      d=(temp>0)?temp*0.1538462:(0.0-temp)*0.1538462;
      i=0.4+0.3*d+0.2*noise.noise_funct(&p3);
    }else{
      i=0.2+0.2*noise.noise_funct(&p3);
    }
  }

  //double i(0);
  //i=noise.noise_funct(p)*20.0-(int)(noise.noise_funct(p)*20.0);
  Color c(color.getR()*i,color.getG()*i,color.getB()*i);
  return c;
}

Color Object::ssin(Point *p){
  Color c0(0.0,0.5,0.0);
  double t((1.0+sin(p->getX()*3.14159265/100.0))/2.0);
  double t_(1.0-t);
  return c0.multiplication(&t_)+color.multiplication(&t);
}
