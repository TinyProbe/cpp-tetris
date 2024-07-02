#ifndef TETRIS_SELECTOR_HPP
#define TETRIS_SELECTOR_HPP

#include <inc/Object.hpp>
#include <inc/Button.hpp>
#include <inc/Setting.hpp>
#include <inc/tetris.h>

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
