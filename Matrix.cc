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

Vector3D Matrix::computVector(double i, double j, double w_w, double h_w, double n_x, double n_y, double distance){
  double u((i+0.5)*(w_w/n_x)-w_w/2.0);
  double v((n_y-j-0.5)*(h_w/n_y)-h_w/2.0);
  double w(distance);

  Vector3D s = (W.multiplication(&w))+(U.multiplication(&u))+(V.multiplication(&v));
  s.normalize();
  return s;
}

Vector3D Matrix::computGrVector(double a){
  double u(-a/2.0+(rand()%11)/10.0*a);
  double v(-a/2.0+(rand()%11)/10.0*a);
  double w(1.0);

  Vector3D _r =(W.multiplication(&w))+(U.multiplication(&u))+(V.multiplication(&v));

  _r.normalize();
  return _r;
}
