#ifndef TETRIS_OPTION_HPP
#define TETRIS_OPTION_HPP

#include <inc/Scene.hpp>
#include <inc/tetris.h>

namespace ttrs {

class Option : public Scene {
 public:
  Option(GameOption *go);
  ~Option();

  virtual void process(Result &result, std::size_t &change) override;
  virtual SceneKind is_what() const override;

 private:

};

} // namespace ttrs

#endif // TETRIS_OPTION_HPP
