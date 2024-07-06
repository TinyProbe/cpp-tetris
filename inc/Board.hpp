#ifndef TETRIS_BOARD_HPP
#define TETRIS_BOARD_HPP

#include <SelfObject.hpp>
#include <tetris.h>

namespace ttrs {

class Holder;
class Queue;
class Block;

class Board : public SelfObject {
 public:
  Board(int x, int y, int hei, int wid, GameOption *go);
  ~Board();

  void link_queue(Queue *queue);
  void link_holder(Holder *holder);
  void next_block();

  bool rotate();
  bool move_left();
  bool move_right();
  bool move_down();
  bool drop_down(Result &result);
  bool recycle();

  virtual void update(Result &result, std::size_t &change) override;
  virtual void rebuild() override;

 private:
  void write_preview();
  void write_block();
  bool check_colision(Block const &block) const;
  void write_to(Texture &to, Block const &block);

  void cleaning();
  bool is_line_full(std::vector<Color> const &line) const;
  bool is_line_empty(std::vector<Color> const &line) const;

  GameOption *game_option_;
  Queue *queue_;
  Holder *holder_;
  Block *block_;
  Texture buffer_;

};

} // namespace ttrs

#endif // TETRIS_BOARD_HPP
