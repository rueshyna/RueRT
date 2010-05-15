#include "RayTrace.h"

Point::Point():X(0),Y(0),Z(0){}
Point::Point(double x, double y, double z):X(x), Y(y), Z(z){}

Point Point::operator+(Point a){
  Point result(this->X+a.getX(), this->Y+a.getY(), this->Z+a.getZ());
  return result;
}

Vector3D Point::operator-(Point a){
  Vector3D result(this->X-a.getX(), this->Y-a.getY(), this->Z-a.getZ());
  return result;
}

Point Point::addVector(Vector3D *a){
  Point result(this->X+a->getX(), this->Y+a->getY(), this->Z+a->getZ());
  return result;
}
double Point::getX(){return X;}
double Point::getY(){return Y;}
double Point::getZ(){return Z;}
