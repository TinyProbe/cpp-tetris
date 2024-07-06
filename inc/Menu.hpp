#ifndef TETRIS_MENU_HPP
#define TETRIS_MENU_HPP

#include <Scene.hpp>
#include <tetris.h>

namespace ttrs {

class Menu : public Scene {
 public:
  Menu();
  ~Menu();

  virtual void process(Result &result, std::size_t &change) override;
  virtual SceneKind is_what() const override;

 private:

};

} // namespace ttrs

#endif // TETRIS_MENU_HPP
