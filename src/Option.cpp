#include <Option.hpp>
#include <Button.hpp>
#include <Selector.hpp>
#include <Setting.hpp>
#include <Image.hpp>

#include <conio.h>

namespace ttrs {

Option::Option(GameOption *go) : Scene() {
  components_.push_back(new Setting(34, 14, "Block Speed"));

  Setting *setting = (Setting *)components_.back();
  setting->set_option_value(&go->block_speed);
  setting->set_option_min(&go->block_speed_min);
  setting->set_option_max(&go->block_speed_max);
  setting->rebuild();

  components_.push_back(new Button(34, 16, "Quit", Result::destruct));
  components_.push_back(new Image(g_kTitle_x, g_kTitle_y, "./res/img/title.txt"));
  components_.push_back(new Selector());

  Selector *selector = (Selector *)components_.back();
  selector->select(components_.begin());
}
Option::~Option() {}

void Option::process(Result &result, std::size_t &change) {
  if (!_kbhit()) { return; }

  int c = _getch();
  switch (c) {
   case 0: case 224:
    c = _getch();
    switch (c) {
     case 72: // ^
      select_up(change); break;
     case 80: // v
      select_down(change); break;
     case 75: // <
      option_down(change); break;
     case 77: // >
      option_up(change); break;
     default: break;
    } break;
   case 13: // enter
    select_exec(result); break;
   case 27: // esc
    result = Result::destruct;
    break;
   default: break;
  }
}

SceneKind Option::is_what() const {
  return SceneKind::option;
}

} // namespace ttrs
