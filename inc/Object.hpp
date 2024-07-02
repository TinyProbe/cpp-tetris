#ifndef TETRIS_OBJECT_HPP
#define TETRIS_OBJECT_HPP

#include <inc/tetris.h>

namespace ttrs {

class Screen;
class Selector;

class Object {
 public:
  Object();
  virtual ~Object();

  virtual void render(Screen &screen) const;
  virtual void update(Result &result, std::size_t &change);
  virtual void render();
  virtual void rebuild();

  virtual Select is_selectable() const;
  virtual void exec(Result &result) const;
  virtual void correction(Selector &selector) const;

  int get_x() const;
  int get_y() const;
  void set_x(int x);
  void set_y(int y);
  std::vector<std::string> const &get_pixels() const;

 protected:
  int x_;
  int y_;
  std::vector<std::string> pixels_;

};

} // namespace ttrs

#endif // TETRIS_OBJECT_HPP
