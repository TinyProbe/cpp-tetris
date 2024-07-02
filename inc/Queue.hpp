#ifndef TETRIS_QUEUE_HPP
#define TETRIS_QUEUE_HPP

#include <inc/SelfObject.hpp>
#include <inc/tetris.h>

#include <list>

namespace ttrs {

class Block;

class Queue : public SelfObject {
 public:
  Queue(int x, int y, std::size_t limit);
  ~Queue();

  void link_game_option(GameOption *go);

  virtual void update(Result &result, std::size_t &change) override;
  virtual void render() override;
  virtual void rebuild() override;

  Block *pop_next();

 private:
  GameOption *game_option_;
  std::list<Block *> queue_;
  std::size_t limit_;

};

} // namespace ttrs

#endif // TETRIS_QUEUE_HPP
