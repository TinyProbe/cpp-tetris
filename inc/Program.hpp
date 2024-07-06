#ifndef TETRIS_PROGRAM_HPP
#define TETRIS_PROGRAM_HPP

#include <Screen.hpp>
#include <tetris.h>

namespace ttrs {

class Scene;

class Program {
 public:
  Program();
  ~Program();

  void run();
  void loop();
  void apply(Result const &result);

 private:
  Screen screen_;
  GameOption game_option_;
  std::vector<Scene *> scenes_;

};

} // namespace ttrs

#endif // TETRIS_PROGRAM_HPP
