#ifndef TETRIS_PAUSE_HPP
#define TETRIS_PAUSE_HPP

#include <Scene.hpp>
#include <tetris.h>

namespace ttrs {

class Pause : public Scene {
 public:
  Pause();
  ~Pause();

  virtual void process(Result &result, std::size_t &change) override;
  virtual SceneKind is_what() const override;

 private:

};

} // namespace ttrs

#endif // TETRIS_PAUSE_HPP
