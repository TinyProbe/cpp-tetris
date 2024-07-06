#include <Object.hpp>
#include <Screen.hpp>

namespace ttrs {

Object::Object() : x_(), y_() {}
Object::~Object() {}

void Object::render(Screen &screen) const {
  for (int i = 0; i < (int)pixels_.size(); ++i) {
    for (int j = 0; j < (int)pixels_[i].size(); ++j) {
      if (isspace(pixels_[i][j])) { continue; }
      int x = x_ + j;
      int y = y_ + i;
      if (x >= 0 && x < (int)g_kWidth &&
          y >= 0 && y < (int)g_kHeight) {
        screen.set_pixel(x, y, pixels_[i][j]);
      }
    }
  }
}

void Object::update(Result &result, std::size_t &change) {
  (void)result;
  (void)change;
}

void Object::render() {
  throw std::string("(x)Object -> (o)[ sub-class -> ... ].");
}

void Object::rebuild() {
  throw std::string("(x)Object -> (o)[ sub-class -> ... ].");
}

Select Object::is_selectable() const {
  return Select::unselectable;
}

void Object::exec(Result &result) const {
  (void)result;
}

void Object::correction(Selector &selector) const {
  (void)selector;
}

int Object::get_x() const { return x_; }

int Object::get_y() const { return y_; }

void Object::set_x(int x) { x_ = x; }

void Object::set_y(int y) { y_ = y; }

std::vector<std::string> const &Object::get_pixels() const {
  return pixels_;
}

} // namespace ttrs
