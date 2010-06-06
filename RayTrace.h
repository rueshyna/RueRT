#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <string>

#define WIDTH 500
#define HEIGHT 500
#define TABLE_NUM 256

using std::cout;
using std::endl;
using std::vector;
using std::random_shuffle;
using std::string;
using std::ifstream;
using std::ofstream;

enum MATERIAL_TYPE{LIGHT, WOOD, FIRE, CLOUD, MARBLE, SINE, CYLINDER, GLOBE};

class Vector3D{
  public:
    Vector3D();
    Vector3D(double x, double y, double z);

    void normalize();
    Vector3D operator+(Vector3D v);
    Vector3D operator-(Vector3D a);
    Vector3D multiplication(double *value);
    Vector3D cross(Vector3D *a);
    double dot(Vector3D *a);

    double getX();
    double getY();
    double getZ();

  private:
    double X;
    double Y;
    double Z;
};

class Point{
  public:
    Point();
    Point(double x, double y, double z);
    Point operator+(Point a);
    Vector3D operator-(Point a);
    Point addVector(Vector3D *a);
    double getX();
    double getY();
    double getZ();

  private:
    double X;
    double Y;
    double Z;
};

class Matrix{
  public:
    void setInitRay(Vector3D *vector);
    Vector3D computVector(double i, double j, double w_w, double h_w, double n_x, double n_y, double distance);
    Vector3D computGrVector(double a);

  private:
    Vector3D U;
    Vector3D V;
    Vector3D W;
};

class Color{
  public:
    Color();
    Color(double rr, double gg, double bb);
    Color operator*(Color c);
    Color operator+(Color c);
    Color multiplication(double *value);
    double getR();
    double getG();
    double getB();
    void setR(double rr);
    void setG(double gg);
    void setB(double bb);
  private:
    double r,g,b;
};

class Noise{
  public:
    vector<int> table;
    vector<Vector3D> table_v;
    Noise();
    void initHashTable();
    Vector3D gamma(Point *p);
    double omega(double t);
    double b_omega(Point *uvw, Point *ijk);
    double noise_funct(Point *p);
};

class Object{
  public:
    double r;
    int isLight;
    Point center;
    Color color;
    MATERIAL_TYPE material;
    Noise noise;
    vector<Color> cImage;
    Object(Point *p, double rr, Color *c, int isL, MATERIAL_TYPE m, Noise *n);
    Object(Point *p, double rr, Color *c, int isL, MATERIAL_TYPE m, Noise *n, vector<Color> *cIm);

    double rayIntersection(Vector3D *_ray, Point *p);
    Color wood_material(Point *p);
    Color ssin(Point *p);
    Color materialColor(Point *p);
    Color marble_material(Point *p);
    Color cloud_material(Point *p);
    Color fire_material(Point *p);
    Color cylinder_material(Point *p);
    Color globe_material(Point *p);
};

class Pixel{
  public:
    Color color;

    Pixel();
    Color rayTrace(Vector3D *v,Point *p, int *step,Color *bgColor, vector<Object> *object,int iObject);

  private:
    double max(double a, double b);
};

class IO{
  public:
    static void save(string filename, vector<Pixel> *image);
    vector<Color> readPicture(string filename);
};
