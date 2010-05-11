#include "RayTrace.h"

void Matrix::setInitRay(Vector3D *vector){
  U = *vector;
  
  Vector3D Vtemp(1.0*U.getY()-0.0*U.getZ(), -(1.0*U.getX()-0.0*U.getZ()), 0.0*U.getX()+0.0*U.getY());
  V=Vtemp;

  Vector3D Wtemp(V.getY()*U.getZ()-V.getZ()*U.getY(), V.getX()*U.getZ()-V.getZ()*U.getX(), V.getZ()*U.getZ());
  W=Wtemp;
}

Point Matrix::computVector(int i, int j, int w_w, int h_w, int n_x, int n_y, double distance, Point *point){
  double u(w_w*(i+0.5)/n_x+w_w/2);
  double v(h_w*(j+0.5)/n_y+h_w/2);
  double w(distance);
  
  double x(u*U.getX()+v*V.getX()+w*W.getX()+(*point).getX());
  double y(u*U.getY()+v*V.getY()+w*W.getY()+(*point).getY());
  double z(u*U.getZ()+v*V.getZ()+w*W.getZ()+(*point).getZ());

  Point s(x, y, z);
  return s;
}
