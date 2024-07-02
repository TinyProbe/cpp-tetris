#ifndef TETRIS_SETTING_HPP
#define TETRIS_SETTING_HPP

#include <inc/Object.hpp>
#include <inc/tetris.h>

namespace ttrs {

class Setting : public Object {
 public:
  Setting(int x, int y, std::string const &s);
  ~Setting();

  virtual void rebuild() override;

  virtual Select is_selectable() const override;
  virtual void exec(Result &result) const override;
  virtual void correction(Selector &selector) const override;

  int get_option_value() const;
  int get_option_min() const;
  int get_option_max() const;
  bool set_option_value(int val);
  void set_option_min(int min);
  void set_option_max(int max);
  void set_option_value(int *val);
  void set_option_min(int *min);
  void set_option_max(int *max);

 private:
  int *option_value_;
  int *option_min_;
  int *option_max_;

};

} // namespace ttrs

#endif // TETRIS_SETTING_HPP
