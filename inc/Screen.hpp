#ifndef TETRIS_SCREEN_HPP
#define TETRIS_SCREEN_HPP

#include <tetris.h>

namespace ttrs {

class Screen {
 public:
  Screen();
  ~Screen();

  void resize(std::size_t const hei, std::size_t const wid, char const c);
  void clear();
  void set_pixel(std::size_t const x, std::size_t const y, char const *s);
  void set_pixel(std::size_t const x, std::size_t const y, char const c);
  void output(std::size_t const x, std::size_t const y) const;

 private:
  std::vector<std::string> pixels_;
};

} // namespace ttrs

#endif // TETRIS_SCREEN_HPP
