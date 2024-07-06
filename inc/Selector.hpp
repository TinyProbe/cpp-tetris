#ifndef TETRIS_SELECTOR_HPP
#define TETRIS_SELECTOR_HPP

#include <Object.hpp>
#include <Button.hpp>
#include <Setting.hpp>
#include <tetris.h>

namespace ttrs {

class Selector : public Object {
 public:
  Selector();
  ~Selector();

  virtual void exec(Result &result) const override;

  void select(ComponentIterator itr);
  ComponentIterator current_select() const;

 private:
  friend void Button::correction(Selector &selector) const;
  friend void Setting::correction(Selector &selector) const;

  ComponentIterator selected_;

};

} // namespace ttrs

#endif // TETRIS_SELECTOR_HPP
