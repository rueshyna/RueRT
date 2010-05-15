#include "RayTrace.h"

double Pixel::max(double a, double b){
  return (a>b)?a:b;
}

Pixel::Pixel(){}

Color Pixel::rayTrace(Vector3D *ray,Point *p,
                       const int *step,Color *bgColor,vector<Object> *objects){
  Color local, reflected, transmitted;
  Vector3D l;
  Vector3D n;
  double t;
  double minDist(10E10);
  int intersectDot = -1;

  if(*step > 1){
    return *bgColor;
  }

  for(vector<Object>::size_type i = 0; i != objects->size(); ++i){
    t = (*objects)[i].rayIntersection(ray,p);
    if(((t >= 0)&& (t < minDist) )&& (!(*objects)[i].isLight)){
      minDist = t;
      intersectDot=i;
    }
  }
  
  if(minDist == 10E10){
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
	//light = i;
      }
    }

    Color Ip = (*objects)[intersectDot].color;
    Color Kd(0.8,0.8,0.8);
    
    vector<Color> diffuse_v;
    vector<Color> specular_v;
    vector<double> dark_v;

    for(vector<Vector3D>::size_type j=0; j!=l_vector.size(); ++j){
      Vector3D n = hitPoint-(*objects)[intersectDot].center;
      n.normalize();
    
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
    }
    
    Color Ia(0.3,0.3,0.3);
    Color Ka(0.2,0.2,0.2);
    Color ambient=Ia * Ka;
    
    for(vector<Vector3D>::size_type i = 0; i !=l_vector.size(); ++i){
      local = local+(diffuse_v[i] + specular_v[i]).multiplication(&(dark_v[i]));
    }
    local = ambient +local;
    return local;
  }

 /* if(t > 0){
    Vector3D nn(ray->getX()*t+p->getX()-(*objects)[intersectDot].center.getX(),
                ray->getY()*t+p->getY()-(*objects)[intersectDot].center.getY(),
	        ray->getZ()*t+p->getZ()-(*objects)[intersectDot].center.getZ());
    n=nn;
    n.normalize();
  
  
    int ilight;

    for(vector<Object>::size_type i = 0; i!=objects->size(); ++i){
     if((*objects)[i].isLight == 1){
       Vector3D ll((*objects)[i].center.getX()-ray->getX()*t+p->getX(),
                   (*objects)[i].center.getY()-ray->getY()*t+p->getY(),
                   (*objects)[i].center.getZ()-ray->getZ()*t+p->getZ());
       ll.normalize();
        l=ll;
        ilight = i;
      }
    }
    double nDotL(l.getX()*n.getX()+l.getY()*n.getY()+l.getZ()*n.getZ());

    Vector3D r(-(l.getX())+2*(nDotL)*n.getX(),
               -(l.getY())+2*(nDotL)*n.getY(),
               -(l.getZ())+2*(nDotL)*n.getZ());
    r.normalize();

    Vector3D v(0-ray->getX(),0-ray->getY(),0-ray->getZ());
    v.normalize();
  
    double diff_max(this->max(0,n.getX()*l.getX()+n.getY()*l.getY()+n.getZ()*l.getZ()));
  
    Color diffuse((*objects)[intersectDot].color.getR()
                      *(0.9+(*objects)[ilight].color.getR()*diff_max),
                  (*objects)[intersectDot].color.getG()
		      *(0.2+(*objects)[ilight].color.getG()*diff_max),
                  (*objects)[intersectDot].color.getB()
                     *(0.2+(*objects)[ilight].color.getB()*diff_max));
    
    double phong_max(this->max(0,v.getX()*r.getX()+v.getY()*r.getY()+v.getZ()*r.getZ()));
    Color phong((*objects)[ilight].color.getR()*
                  (*objects)[intersectDot].color.getR()*pow(phong_max,128),
                (*objects)[ilight].color.getG()*
	          (*objects)[intersectDot].color.getG()*pow(phong_max,128),
	        (*objects)[ilight].color.getB()*
                  (*objects)[intersectDot].color.getB()*pow(phong_max,128));
  
    Color lo(diffuse.getR()+phong.getR(),
             diffuse.getG()+phong.getG(),
             diffuse.getB()+phong.getB());
    return lo;
  }else{
    return *bgColor;
  }*/
}

