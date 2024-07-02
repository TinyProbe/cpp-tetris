#ifndef TETRIS_BLOCK_HPP
#define TETRIS_BLOCK_HPP

#include <inc/SelfObject.hpp>
#include <inc/tetris.h>

namespace ttrs {

class Block : public SelfObject {
 public:
  Block(int x, int y, BlockKind block_kind, bool is_blank);
  ~Block();

  void link_game_option(GameOption *go);

  virtual void update(Result &result, std::size_t &change) override;
  virtual void rebuild() override;

  BlockKind get_block_kind() const;
  Texture const &get_texture() const;
  bool is_blank() const;
  void set_blank(bool blank);
  void rotate(std::size_t time);
  void time_reset();

 private:
  BlockKind block_kind_;
  bool is_blank_;
  int rotate_;
  Time time_;
  GameOption *game_option_;

};

} // namespace ttrs

#endif // TETRIS_BLOCK_HPP
