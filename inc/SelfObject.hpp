#ifndef TETRIS_SELFOBJECT_HPP
#define TETRIS_SELFOBJECT_HPP

#include <inc/Object.hpp>
#include <inc/tetris.h>

namespace ttrs {

class SelfObject : public Object {
 public:
  SelfObject();
  virtual ~SelfObject();

  virtual void render() override;

 protected:
  Texture texture_;

};

} // namespace ttrs

#endif // TETRIS_SELFOBJECT_HPP
