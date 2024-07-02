#include <inc/Screen.hpp>

#include <string.h>
#include <iostream>

namespace ttrs {

Screen::Screen() {}
Screen::~Screen() {}

void Screen::resize(std::size_t const hei,
                    std::size_t const wid,
                    char const c) {
  pixels_.resize(hei, std::string(wid, c));
}

void Screen::clear() {
  for (std::string &s : pixels_) {
    s.assign(s.size(), ' ');
  }
}

void Screen::set_pixel(std::size_t const x,
                       std::size_t const y,
                       char const *s) {
  std::size_t len = strlen(s);
  if (y >= pixels_.size() || x + len > pixels_[y].size()) {
    throw std::string("An access was detected with invalid pixel coordinates.");
  }
  memcpy(&pixels_[y][x], s, len);
}

void Screen::set_pixel(std::size_t const x,
                       std::size_t const y,
                       char const c) {
  if (y >= pixels_.size() || x >= pixels_[y].size()) {
    throw std::string("An access was detected with invalid pixel coordinates.");
  }
  pixels_[y][x] = c;
}

void Screen::output(std::size_t const x, std::size_t const y) const {
  for (int i = 0; i < (int)pixels_.size(); ++i) {
    gotoxy(x, y + i);
    std::cout << pixels_[i] << std::flush;
  }
}

} // namespace ttrs
