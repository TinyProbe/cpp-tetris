#include <inc/Menu.hpp>
#include <inc/Button.hpp>
#include <inc/Selector.hpp>
#include <inc/Image.hpp>

#include <conio.h>

namespace ttrs {

Menu::Menu() : Scene() {
  components_.push_back(new Button(34, 14, "Start Game", Result::construct_game));
  components_.push_back(new Button(34, 16, "Options", Result::construct_option));
  components_.push_back(new Button(34, 18, "Quit", Result::destruct));
  components_.push_back(new Image(g_kTitle_x, g_kTitle_y, "./res/img/title.txt"));
  components_.push_back(new Selector());

  Selector *selector = (Selector *)components_.back();
  selector->select(components_.begin());
}
Menu::~Menu() {}

void Menu::process(Result &result, std::size_t &change) {
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
     default: break;
    }
    break;
   case 13: // enter
    select_exec(result); break;
   default: break;
  }
}

SceneKind Menu::is_what() const {
  return SceneKind::menu;
}

} // namespace ttrs
