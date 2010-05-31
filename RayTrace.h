#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::vector;

class Vector3D{
  public:
    Vector3D();
    Vector3D(double x, double y, double z);
    
    void normalize();
    Vector3D operator+(Vector3D v);
    Vector3D operator-(Vector3D a);
    Vector3D multiplication(double *value);
    Vector3D cross(Vector3D *a);
    double dot(Vector3D *a);
    
    double getX();
    double getY();
    double getZ();

  private:
    double X;
    double Y;
    double Z;
};

class Point{
  public:
    Point();
    Point(double x, double y, double z);
    Point operator+(Point a);
    Vector3D operator-(Point a);
    Point addVector(Vector3D *a);
    double getX();
    double getY();
    double getZ();
    
  private:
    double X;
    double Y;
    double Z;
};
  
class Matrix{
  public:
    void setInitRay(Vector3D *vector);
    Vector3D computVector(double i, double j, double w_w, double h_w, double n_x, double n_y, double distance);
    Vector3D computGrVector(double a);

  private:
    Vector3D U;
    Vector3D V;
    Vector3D W;
};

class Color{
  public:
    Color();
    Color(double rr, double gg, double bb);
    Color operator*(Color c);
    Color operator+(Color c);
    Color multiplication(double *value);
    double getR();
    double getG();
    double getB();
    void setR(double rr);
    void setG(double gg);
    void setB(double bb);
  private:
    double r,g,b;
};

class Object{
  public:
    double r;
    int isLight;
    Point center;
    Color color;
    
    double rayIntersection(Vector3D *_ray, Point *p);
    Object(Point *p, double rr, Color *c, int isL);
};

class Pixel{
  public:
    Color color;

    Pixel();
    Color rayTrace(Vector3D *v,Point *p, int *step,Color *bgColor, vector<Object> *object,int iObject);

  private:
    double max(double a, double b);
};
