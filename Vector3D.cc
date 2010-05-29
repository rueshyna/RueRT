#include "RayTrace.h"


Vector3D::Vector3D():X(0), Y(0), Z(0){}
Vector3D::Vector3D(double x, double y, double z):X(x), Y(y), Z(z){}

void Vector3D::normalize(){
  double unit(sqrt(X*X+Y*Y+Z*Z));
  X = X/unit;
  Y = Y/unit;
  Z = Z/unit;
}

Vector3D Vector3D::operator+(Vector3D a){
  Vector3D result(this->X+a.getX(), this->Y+a.getY(), this->Z+a.getZ());
  return result;
}

Vector3D Vector3D::operator-(Vector3D a){
  Vector3D result(this->X-a.getX(), this->Y-a.getY(), this->Z-a.getZ());
  return result;
}

Vector3D Vector3D::multiplication(double *value){
  Vector3D result(this->X*(*value),this->Y*(*value), this->Z*(*value));
  return result;
}

Vector3D Vector3D::cross(Vector3D *a){
  Vector3D result(this->getY()*a->getZ()-this->getZ()*a->getY(),
                -(this->getX()*a->getZ()-this->getZ()*a->getX()),
                  this->getX()*a->getY()-this->getY()*a->getX());
  return result;
}

double Vector3D::dot(Vector3D *a){
  double result(this->X*a->getX()+this->Y*a->getY()+this->Z*a->getZ());
  return result;
}

double Vector3D::getX(){return X;}
double Vector3D::getY(){return Y;}
double Vector3D::getZ(){return Z;}
