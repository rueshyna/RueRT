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
    return *bgColor;
  }
    //cout<<"\n" <<ray->getX()<<" "<<ray->getY()<<" "<<ray->getZ()<<endl;

  for(vector<Object>::size_type i = 0; i != objects->size(); ++i){
    t = (*objects)[i].rayIntersection(ray,p);
    if((t > 0)&&(t < minDist)&&(!(*objects)[i].isLight)&& i != iObject){
      minDist = t;
      intersectDot=i;
    }
  }
  //cout <<" "<< t<<endl;
  //cout <<s.getX()<<" "<<s.getY()<<" "<<s.getZ()<<endl;
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

    Color Ip = (*objects)[intersectDot].color;
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
          dark = 0.05;
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

      Vector3D r_a(r.getX()+1.0/(rand()%50), r.getY()+1.0/(rand()%50),r.getZ());
      Color refColor = rayTrace(&r_a, &hitPoint,step, bgColor,objects,intersectDot);
      refColor_v.push_back(refColor);
    }

    Color Ia(0.3,0.3,0.3);
    Color Ka(0.2,0.2,0.2);
    Color ambient=Ia * Ka;


    for(vector<Vector3D>::size_type i = 0; i !=l_vector.size(); ++i){
      local = local+(diffuse_v[i] + specular_v[i]).multiplication(&(dark_v[i]));
      Color Kr(0.2*1.0/(i+2.0),0.2*1.0/(i+2.0),0.2*1.0/(i+2.0));
      reflected = reflected+refColor_v[i]*Kr;
    }
    local = ambient +local;

    return local+reflected;
  }
}

