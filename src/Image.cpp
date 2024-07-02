#include <inc/Image.hpp>

#include <fstream>

namespace ttrs {

Image::Image(int x, int y, std::string const &filename)
    : Object() {
  x_ = x;
  y_ = y;
  std::ifstream file(filename);
  std::string s;
  if (!file.is_open()) {
    throw std::string("Failed to open file.");
  }
  while (std::getline(file, s)) {
    pixels_.push_back(s);
  }
  file.close();
}
Image::~Image() {}

} // namespace ttrs
