#include "RayTrace.h"

    Color::Color():r(0),g(0),b(0){}
    Color::Color(double rr, double gg, double bb) : r(rr), g(gg), b(bb){}
    double Color::getR(){return r;}
    double Color::getG(){return g;}
    double Color::getB(){return b;}
    void Color::setR(double rr){r=rr;}
    void Color::setG(double gg){g=gg;}
    void Color::setB(double bb){b=bb;}
