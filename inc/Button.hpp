#ifndef TETRIS_BUTTON_HPP
#define TETRIS_BUTTON_HPP

#include <Object.hpp>
#include <tetris.h>

namespace ttrs {

class Selector;

class Button : public Object {
 public:
  Button(int x, int y, std::string const &s, Result exec);
  ~Button();

  virtual Select is_selectable() const override;
  virtual void exec(Result &result) const override;
  virtual void correction(Selector &selector) const override;

 private:
  Result exec_;

};

} // namespace ttrs

#endif // TETRIS_BUTTON_HPP
