#ifndef TETRIS_IMAGE_HPP
#define TETRIS_IMAGE_HPP

#include <inc/Object.hpp>
#include <inc/tetris.h>

namespace ttrs {

class Image : public Object {
 public:
  Image(int x, int y, std::string const &filename);
  ~Image();

 private:

};

} // namespace ttrs

#endif // TETRIS_IMAGE_HPP
