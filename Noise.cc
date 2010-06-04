#include "RayTrace.h"

#define TABLE_NUM 256

Noise::Noise(){}

void Noise::initHashTable(){
  for(vector<int>::size_type i=0; i<TABLE_NUM; ++i ){
    table.push_back(i);
  }

  random_shuffle(table.begin(),table.end());

  while(table_v.size()<TABLE_NUM){
    //normalize problem;
    Vector3D v(2.0*(rand()%1000/1000.0)-1,2.0*(rand()%1000/1000.0)-1,2.0*(rand()%1000/1000.0)-1);
    if((pow(v.getX(),2.0)+pow(v.getY(),2.0)+pow(v.getZ(),2.0)) < 1){
      v.normalize();
      table_v.push_back(v);
    }
  }
}

Vector3D Noise::gamma(Point *p){
  return table_v[abs((int)p->getX()+table[abs((int)p->getY()+table[abs((int)p->getZ())%TABLE_NUM])%TABLE_NUM])%TABLE_NUM];
}

double Noise::omega(double t){
  if(t<1 && t>-1){
    return (t>0)?2.0*pow(t,3.0)-3.0*pow(t,2.0)+1.0:2.0*pow(0.0-t,3.0)-3.0*pow(t,2.0)+1.0;
  }else{
    return 0;
  }
}

double Noise::b_omega(Point *uvw, Point *ijk){
  Vector3D g(gamma(ijk));
  return omega(uvw->getX())*omega(uvw->getY())*omega(uvw->getZ())*(uvw->getX()*g.getX()+uvw->getY()*g.getY(),uvw->getZ()*g.getZ());
}

double Noise::noise_funct(Point *p){
  double result(0.0);
  for(int i=floor(p->getX()); i<floor(p->getX())+2; ++i){
    for(int j=floor(p->getY()); j<floor(p->getY())+2; ++j){
      for(int k=floor(p->getZ()); k<floor(p->getZ())+2; ++k){
        Point uvw(p->getX()-i, p->getY()-j, p->getZ()-k);
        Point ijk(i,j,k);
        result += b_omega(&uvw,&ijk);
      }
    }
  }
  return (result+1.0)*0.7;
}
