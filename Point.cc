#include "RayTrace.h"

Point::Point():X(0),Y(0),Z(0){}
Point::Point(double x, double y, double z):X(x), Y(y), Z(z){}
double Point::getX(){return X;}
double Point::getY(){return Y;}
double Point::getZ(){return Z;}
