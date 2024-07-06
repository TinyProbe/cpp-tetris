#include <Setting.hpp>
#include <Selector.hpp>

namespace ttrs {

Setting::Setting(int x, int y, std::string const &s)
    : option_value_(), option_min_(), option_max_() {
  x_ = x;
  y_ = y;
  pixels_.push_back(s);
}
Setting::~Setting() {}

void Setting::rebuild() {
  pixels_.back().resize(g_kOption_width, ' ');
  pixels_.back() += std::to_string(*option_value_);
}

Select Setting::is_selectable() const {
  return Select::setting;
}

void Setting::exec(Result &result) const {
  (void)result;
}

void Setting::correction(Selector &selector) const {
  selector.x_ = x_ + g_kOption_width -
      (int)g_kSelector_setting_left.size() - 1;
  selector.y_ = y_;
  selector.pixels_.back().clear();
  selector.pixels_.back() += g_kSelector_setting_left;
  selector.pixels_.back() +=
      std::string(std::to_string(*option_value_).size() + 2, ' ');
  selector.pixels_.back() += g_kSelector_setting_right;
}

int Setting::get_option_value() const { return *option_value_; }
int Setting::get_option_min() const { return *option_min_; }
int Setting::get_option_max() const { return *option_max_; }

bool Setting::set_option_value(int val) {
  if (val >= *option_min_ && val <= *option_max_) {
    *option_value_ = val;
    return true;
  }
  return false;
}
void Setting::set_option_min(int min) { *option_min_ = min; }
void Setting::set_option_max(int max) { *option_max_ = max; }

void Setting::set_option_value(int *val) { option_value_ = val; }
void Setting::set_option_min(int *min) { option_min_ = min; }
void Setting::set_option_max(int *max) { option_max_ = max; }

} // namespace ttrs
