#include <SelfObject.hpp>

#include <iostream>

namespace ttrs {

SelfObject::SelfObject() : Object() {}
SelfObject::~SelfObject() {}

void SelfObject::render() {
  for (int i = 0; i < (int)pixels_.size(); ++i) {
    gotoxy(x_, y_ + i);
    std::cout << pixels_[i] << std::flush;
  }
}

} // namespace ttrs
