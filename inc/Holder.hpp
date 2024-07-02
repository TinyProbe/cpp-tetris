#ifndef TETRIS_HOLDER_HPP
#define TETRIS_HOLDER_HPP

#include <inc/SelfObject.hpp>
#include <inc/tetris.h>

namespace ttrs {

class Block;

class Holder : public SelfObject {
 public:
  Holder(int x, int y, int hei, int wid);
  ~Holder();

  void link_game_option(GameOption *go);

  virtual void rebuild() override;

 private:
  GameOption *game_option_;
  Block *block_;

};

} // namespace ttrs

#endif // TETRIS_HOLDER_HPP
