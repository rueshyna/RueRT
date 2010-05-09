#include <vector>
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

class Vector3D{
  public:
    Vector3D():X(0), Y(0), Z(0){}
    Vector3D(double x, double y, double z):X(x), Y(y), Z(z){}
    void normalize(){
     double unit;
     unit = sqrt(X*X+Y*Y+Z*Z);
     X = X/unit;
     Y = Y/unit;
     Z = Z/unit;
    }

    double getX(){return X;}
    double getY(){return Y;}
    double getZ(){return Z;}

  private:
    double X;
    double Y;
    double Z;
};

class Point{
  public:
    Point():X(0),Y(0),Z(0){}
    Point(double x, double y, double z):X(x), Y(y), Z(z){};

    double getX(){return X;}
    double getY(){return Y;}
    double getZ(){return Z;}
    
    Point operator+(Point p){
      Point pp(p.getX()+X, p.getY()+Y, p.getZ()+Z);
      return pp;
    }

    Point operator-(Point p){
      Point pp(p.getX()-X, p.getY()-Y, p.getZ()-Z);
      return pp;
    }
    
    Point operator*(Point p){
      Point pp(p.getX()*X, p.getY()*Y, p.getZ()*Z);
      return pp;
    }
  private:
    double X;
    double Y;
    double Z;
};
  
class Matrix{
  public:
    void setInitRay(Vector3D *vector){
      U = *vector;
      
      Vector3D Vtemp(1.0*U.getY()-0.0*U.getZ(), -(1.0*U.getX()-0.0*U.getZ()), 0.0*U.getX()+0.0*U.getY());
      V=Vtemp;

      Vector3D Wtemp(V.getY()*U.getZ()-V.getZ()*U.getY(), V.getX()*U.getZ()-V.getZ()*U.getX(), V.getZ()*U.getZ());
      W=Wtemp;
    }
    
    Point computVector(int i, int j, int w_w, int h_w, int n_x, int n_y, double distance, Point *point){
      double u(w_w*(i+0.5)/n_x+w_w/2);
      double v(h_w*(j+0.5)/n_y+h_w/2);
      double w(distance);
      
      double x(u*U.getX()+v*V.getX()+w*W.getX()+(*point).getX());
      double y(u*U.getY()+v*V.getY()+w*W.getY()+(*point).getY());
      double z(u*U.getZ()+v*V.getZ()+w*W.getZ()+(*point).getZ());

      Point s(x, y, z);
      return s;
    }

    private:
      Vector3D U;
      Vector3D V;
      Vector3D W;
};

class Color{
  public:
    Color():r(0),g(0),b(0){}
    Color(double rr, double gg, double bb) : r(rr), g(gg), b(bb){}
    double getR(){return r;}
    double getG(){return g;}
    double getB(){return b;}
    void setR(double rr){r=rr;}
    void setG(double gg){g=gg;}
    void setB(double bb){b=bb;}
  private:
    double r,g,b;
};

class Object{
  public:
    double r, area;
    Vector3D ray;
    Point center;
    Color color;
    
    Point rayIntersection(Point *screen, Point *eye){
      Vector3D ray((*s).getX()-(*eye).getZ(),(*s).getY()-(*eye).getY(),(*s).getZ()-(*eye).getZ());
      ray.normalize();
      Point NaN(NAN,NAN,NAN);

      double t;
      double a(1);
      double b(2*(ray.getX()*(center.getX()-(*eye).getX())+ray.getY()*(center.getY()-(*eye).getY())+ray.getZ()*(center.getZ()-(*eye).getZ())));
      double c(pow(center.getX()-(*eye).getX(),2)+pow(center.getY()-(*eye).getY(),2)+pow(center.getZ()-(*eye).getZ(),2));
      double d((pow(b,2)-4*a*c));

      if(d < 0){
        return NaN;
      }
      
      double t0((-b-sqrt(d))/2);

      if(d = 0){
        t = t0; 
        Point sectionPoint((*eye).getX()+ray.getX()*t,(*eye).getY()+ray.getY()*t,(*eye).getZ()+ray.getZ()*t);
        return sectionPoint;
      }
      
      if(t0 <= 0){
        double t1((-b+sqrt(d))/2);
	
	if(t1 <= 0){
	  return NaN;
	}else{
	  t = t1;
	}
      }else{
        t=t0;
      }
      
      Point sectionPoint((*eye).getX()+ray.getX()*t,(*eye).getY()+ray.getY()*t,(*eye).getZ()+ray.getZ()*t);
      return sectionPoint;
    }

    Object(Point *p, double rr, Color *c):r(rr){
      center = *p;
      area = r*r*M_PI;
      color = *c;
    }
};

class Pixel{
  public:
    Vector3D ray;
    Color color;
};
