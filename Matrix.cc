#include "RayTrace.h"

void Matrix::setInitRay(Vector3D *vector){
  W = *vector;
  W.normalize();
  
  Vector3D viewUp(0,0,1);
  U=W.cross(&viewUp);
  U.normalize();

  V=U.cross(&W);
  V.normalize();
}

Vector3D Matrix::computVector(int i, int j, int w_w, int h_w, int n_x, int n_y, double distance){
  double u((i+0.5)*(w_w/n_x)-w_w/2);
  double v((j+0.5)*(h_w/n_y)-h_w/2);
  double w(distance);
  
  double x(u*U.getX()+v*V.getX()+w*W.getX());
  double y(u*U.getY()+v*V.getY()+w*W.getY());
  double z(u*U.getZ()+v*V.getZ()+w*W.getZ());
  
  Vector3D s(x, y, z);
  s.normalize();
  return s;
}
