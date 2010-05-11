#include "RayTrace.h"


Vector3D::Vector3D():X(0), Y(0), Z(0){}
Vector3D::Vector3D(double x, double y, double z):X(x), Y(y), Z(z){}

void Vector3D::normalize(){
  double unit(sqrt(X*X+Y*Y+Z*Z));
  X = X/unit;
  Y = Y/unit;
  Z = Z/unit;
}
double Vector3D::getX(){return X;}
double Vector3D::getY(){return Y;}
double Vector3D::getZ(){return Z;}
