#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include <inc/Scene.hpp>
#include <inc/tetris.h>

namespace ttrs {

class Game : public Scene {
 public:
  Game(GameOption *go);
  ~Game();

  virtual void process(Result &result, std::size_t &change) override;
  virtual SceneKind is_what() const override;

 private:
  void rotate(std::size_t &change);
  void left(std::size_t &change);
  void right(std::size_t &change);
  void down(std::size_t &change);
  void drop(Result &result, std::size_t &change);

  GameOption *game_option_;

};

} // namespace ttrs

#endif // TETRIS_GAME_HPP
