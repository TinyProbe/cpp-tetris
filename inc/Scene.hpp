#ifndef TETRIS_SCENE_HPP
#define TETRIS_SCENE_HPP

#include <tetris.h>

namespace ttrs {

class Screen;
class Object;

class Scene {
 public:
  Scene();
  virtual ~Scene();

  virtual void render(Screen &screen) const;
  virtual void render();
  virtual void update(Result &result, std::size_t &change);
  virtual void process(Result &result, std::size_t &change);
  virtual SceneKind is_what() const;

 protected:
  void select_up(std::size_t &change);
  void select_down(std::size_t &change);
  void select_exec(Result &result);
  void option_down(std::size_t &change);
  void option_up(std::size_t &change);

  std::vector<Object *> components_;

};

} // namespace ttrs

#endif // TETRIS_SCENE_HPP
