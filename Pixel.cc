#include "RayTrace.h"

double Pixel::max(double a, double b){
  return (a>b)?a:b;
}

Pixel::Pixel(){}

Color Pixel::rayTrace(Vector3D *ray,Point *p,
                       int *step,Color *bgColor,vector<Object> *objects,int iObject){
  Color local, reflected, transmitted;
  Vector3D l;
  Vector3D n;
  double t;
  double minDist(10E6);
  int intersectDot = -1;

  if(*step > 3){
    Color c_last(0,0,0);
    return c_last;
  }

  for(vector<Object>::size_type i = 0; i != objects->size(); ++i){
    t = (*objects)[i].rayIntersection(ray,p);
    if((t > 0)&&(t < minDist)&&(!(*objects)[i].isLight)&& i != iObject){
      minDist = t;
      intersectDot=i;
    }
  }

  if(intersectDot == -1){
    return *bgColor;
  }else{
    vector<Vector3D> l_vector;
    Vector3D l;
    int light;

    Vector3D hitRay = ray->multiplication(&minDist);
    Point hitPoint = p->addVector(&hitRay);

    for(vector<Object>::size_type i=0; i!=objects->size(); ++i){
      if((*objects)[i].isLight){
        Vector3D ll = (*objects)[i].center - hitPoint;
        l = ll;
        l.normalize();
        l_vector.push_back(l);
      }
    }

    Color Ip = (*objects)[intersectDot].materialColor(&hitPoint);
    Color Kd(0.5,0.5,0.5);

    vector<Color> diffuse_v;
    vector<Color> specular_v;
    vector<Color> refColor_v;
    vector<double> dark_v;

    Vector3D n = hitPoint-(*objects)[intersectDot].center;
    n.normalize();

    for(vector<Vector3D>::size_type j=0; j!=l_vector.size(); ++j){
      //shadow
      double s;
      double dark = 1;

      for(vector<Object>::size_type i=0; i!=objects->size();++i){
        s = (*objects)[i].rayIntersection(&(l_vector[j]),&hitPoint);
        if(s>0 && !(*objects)[i].isLight && (i !=intersectDot)){
          dark = 0;
        }
      }

      dark_v.push_back(dark);

      double rd(this->max(0,(n.dot(&(l_vector[j])))));

      Color diffuse = Ip*(Kd.multiplication(&rd));
      diffuse_v.push_back(diffuse);

      double twoNDotL(2*n.dot(&(l_vector[j])));

      Vector3D r(n.multiplication(&twoNDotL) - l_vector[j]);
      r.normalize();

      Vector3D zero(0,0,0);
      Vector3D v = zero - (*ray);
      v.normalize();

      Color Ks(0.4,0.4,0.4);
      double rs(pow(max(0,r.dot(&v)),32));
      Color specular = Ip * Ks.multiplication(&rs);
      specular_v.push_back(specular);

      *step += 1;

      //glossy reflaction matrix
      Matrix gr_matrix;
      gr_matrix.setInitRay(&r);
      Vector3D r_a = gr_matrix.computGrVector(0.12);

      Color refColor = rayTrace(&r_a, &hitPoint,step, bgColor,objects,intersectDot);
      refColor_v.push_back(refColor);
    }

    Color Ia(0.1,0.1,0.1);
    Color Ka(0.1,0.1,0.1);
    Color ambient=Ia * Ka;

    for(vector<Vector3D>::size_type i = 0; i !=l_vector.size(); ++i){
      double c_dark(dark_v[i]/l_vector.size());
      local = local+(diffuse_v[i] + specular_v[i]).multiplication(&(c_dark));
      Color Kr(0.2*1.0/(i+2.0),0.2*1.0/(i+2.0),0.2*1.0/(i+2.0));
      reflected = reflected+refColor_v[i]*Kr;
    }
    local = ambient +local;

    return local+reflected;
  }
}

