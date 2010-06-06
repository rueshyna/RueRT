#include "RayTrace.h"
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

Object::Object(Point *p, double rr, Color *c, int isL, MATERIAL_TYPE m, Noise *n, vector<Color> *cIm):r(rr), isLight(isL), material(m){
  center = *p;
  color = *c;
  noise = *n;
  cImage = *cIm;
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
    return fire_material(p);
  case CLOUD :
    return cloud_material(p);
  case MARBLE :
    return marble_material(p);
  case SINE:
    return ssin(p);
  case CYLINDER :
    return cylinder_material(p);
  case GLOBE :
    return globe_material(p);
  default :
    return color;
  }
}

#define PI 3.141592654
Color Object::cylinder_material(Point *p){
  double width(cImage[(cImage.size()-1)].getR());
  double height(cImage[(cImage.size()-1)].getG());
  double u,v,v_,u_;
  u = atan((p->getY()-center.getY())/(p->getX()-center.getX()))*180.0/PI*2.0*(width-1)/360.0;
  v = (p->getZ()-center.getZ())/(2.0*r)*(height-1);
  u_= (int)(u-width/2);
  v_= (int)(v+height/2);
  return cImage[((int)(width*((height-v_-1))+u_))];
}

Color Object::globe_material(Point *p){
  double width(cImage[(cImage.size()-1)].getR());
  double height(cImage[(cImage.size()-1)].getG());
  double u,v,v_,u_;
  //v=arcos(z/r)/pi
  v = acos((p->getZ()-center.getZ())/r)*180.0/PI;
  if((p->getY()-center.getY())>=0){
    u=acos((p->getX()-center.getX())/(r*sin(v*PI/180.0)))*180.0/PI;
  }else{
    u=acos((p->getX()-center.getX())/(r*sin(v*PI/180.0)))*180.0/PI;
  }

  u_= (int)((180.0-u)*(width-1.0)/180.0-width/2);
  v_= (int)(v*(height-1.0)/360.0+height/2);

  return cImage[((int)(width*((height-v_-1))+u_))];
}
Color Object::fire_material(Point *p){
  Point p1(p->getX()/7.0,p->getY()/5.0,p->getZ()/1.0);
  double n(noise.noise_funct(&p1)/0.5-1);
  double i(n+0.9);
  i = (i>0)?i:0.0-i;
  Color c(0.9,0.2,0.1);
  return c.multiplication(&i);
}

Color Object::wood_material(Point *p){
  double i(0);
  Point p2(p->getX()/120.0,p->getY()/120.0,p->getZ()/120.0);
  i=noise.noise_funct(&p2)*50.0-(int)(noise.noise_funct(&p2)*50.0);
  /*double radius(sqrt(pow(p->getX(),2.0)+pow(p->getZ(),2.0)));
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
    Color c(0.1,0.2,0.1);*/
  return color.multiplication(&i);
  //}
}

Color Object::cloud_material(Point *p){
  Point p1(p->getX()/30.0+20.6,p->getY()/20.0+50.5,p->getZ()/30.0+70.0);
  double i(noise.noise_funct(&p1)*2.0);
  return color.multiplication(&i);
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
  return color.multiplication(&i);
}

Color Object::ssin(Point *p){
  Color c0(0.0,0.5,0.0);
  double t((1.0+sin(p->getX()*3.14159265/100.0))/2.0);
  double t_(1.0-t);
  return c0.multiplication(&t_)+color.multiplication(&t);
}
