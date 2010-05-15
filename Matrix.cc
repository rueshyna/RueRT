#include "RayTrace.h"

void Matrix::setInitRay(Vector3D *vector){
  W = *vector;
  W.normalize();
  
  Vector3D viewUp(0,0,1);
  //Vector3D Utemp(W.getY()*1.0-W.getZ()*0.0, -(W.getX()*1.0-W.getZ()*0.0), W.getX()*0.0+W.getY()*0.0);
  // U=Utemp;
  U=W.cross(&viewUp);
  U.normalize();

  //Vector3D Vtemp(U.getY()*W.getZ()-U.getZ()*W.getY(), -(U.getX()*W.getZ()-U.getZ()*W.getX()), U.getX()*W.getY()-U.getY()*W.getX());
  //V=Vtemp;
  V=U.cross(&W);
  V.normalize();
}

Vector3D Matrix::computVector(int i, int j, int w_w, int h_w, int n_x, int n_y, double distance){
  double u(w_w*(i+0.5)/n_x-w_w/2);
  double v(h_w*(j+0.5)/n_y-h_w/2);
  double w(distance);
  
  double x(u*U.getX()+v*V.getX()+w*W.getX());
  double y(u*U.getY()+v*V.getY()+w*W.getY());
  double z(u*U.getZ()+v*V.getZ()+w*W.getZ());

  Vector3D s(x, y, z);
  s.normalize();
  return s;
}
