#include "RayTrace.h"

void IO::save(string filename, vector<Pixel> *image){
  ofstream outfile;

  outfile.open(filename.c_str(),ofstream::out);
  outfile <<"P3\n"<< WIDTH<<" "<< HEIGHT <<"\n"<< 255 <<"\n";

  double r, g, b;

  for (vector<Object>::size_type j = 0; j < image->size(); ++j) {
    r = (*image)[j].color.getR();
    g = (*image)[j].color.getG();
    b = (*image)[j].color.getB();
    outfile << floor(r*255)<<" "<< floor(g*255) <<" "<< floor(b*255) << "\n";
  }
  outfile.close();
  outfile.clear();
}

/*color_v's last element is width and height*/
vector<Color> IO::readPicture(string filename){
  vector<Color> color_v;
  ifstream picture_f;

  picture_f.open(filename.c_str());

  string magic;
  int width = 0;
  int height = 0;
  int pixel_max = 0;
  double r,g,b;

  picture_f >> magic >> width >> height >> pixel_max;

  Color c(width, height, 0.0);

  while(picture_f>>r>>g>>b){
    Color cc(r/255.0,g/255.0,b/255.0);
    color_v.push_back(cc);
  }

  color_v.push_back(c);
  picture_f.close();
  picture_f.clear();
  return color_v;
}
