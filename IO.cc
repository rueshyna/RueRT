#include "RayTrace.h"

void IO::save(string filename, vector<Pixel> *image){
  std::ofstream outfile;

  outfile.open(filename.c_str(),std::ofstream::out);
  outfile <<"P3\n"<< WIDTH<<" "<< HEIGHT <<"\n"<< 255 <<"\n";

  double r, g, b;

  for (vector<Object>::size_type j = 0; j < image->size(); ++j) {
    r = (*image)[j].color.getR();
    g = (*image)[j].color.getG();
    b = (*image)[j].color.getB();
    outfile << floor(r*255)<<" "<< floor(g*255) <<" "<< floor(b*255) << "\n";
  }
  outfile.close();
}
