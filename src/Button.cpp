#include <Button.hpp>
#include <Selector.hpp>

namespace ttrs {

Button::Button(int x, int y, std::string const &s, Result exec)
    : exec_(exec) {
  x_ = x;
  y_ = y;
  pixels_.push_back(s);
}
Button::~Button() {}

Select Button::is_selectable() const {
  return Select::button;
}

void Button::exec(Result &result) const {
  result = exec_;
}

void Button::correction(Selector &selector) const {
  selector.x_ = x_ - (int)g_kSelector_button_left.size() - 1;
  selector.y_ = y_;
  selector.pixels_.back().clear();
  selector.pixels_.back() += g_kSelector_button_left;
  selector.pixels_.back() += std::string(pixels_.back().size() + 2, ' ');
  selector.pixels_.back() += g_kSelector_button_right;
}

} // namespace ttrs
