#include <Program.hpp>
#include <Menu.hpp>
#include <Game.hpp>
#include <Option.hpp>
#include <Pause.hpp>

#include <windows.h>
#include <iostream>

namespace ttrs {

Program::Program() {
  screen_.resize(g_kHeight, g_kWidth, ' ');
  scenes_.push_back(new Menu());

  game_option_.block_speed = g_kOption_game_speed_default;
  game_option_.block_speed_min = g_kOption_game_speed_min;
  game_option_.block_speed_max = g_kOption_game_speed_max;
}
Program::~Program() {}

void Program::run() {
  // Prepare before enter a loop.
  SetConsoleOutputCP(CP_UTF8);
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  show_console_cursor(false);
  std::system("cls");
  loop();
  show_console_cursor(true);
  std::system("cls");
}

void Program::loop() {
  Scene *current_scene = nullptr;
  Result result = Result::nothing_to_do;
  std::size_t change = 1;

  while (scenes_.size() > 0) {
    current_scene = scenes_.back();
    if (result != Result::nothing_to_do || change > 0) {
      if (current_scene->is_what() != SceneKind::game) {
        current_scene->render(screen_);
      } else {
        current_scene->render();
      }
      result = Result::nothing_to_do;
      change = 0;
    }
    current_scene->update(result, change);
    current_scene->process(result, change);
    apply(result);
  }
}

void Program::apply(Result const &result) {
  switch (result) {
   case Result::construct_game:
    scenes_.push_back(new Game(&game_option_));
   break;
   case Result::construct_option:
    scenes_.push_back(new Option(&game_option_));
   break;
   case Result::construct_pause:
    scenes_.push_back(new Pause());
   break;
   case Result::destruct_to_main:
    while (scenes_.size() > 1) {
      delete scenes_.back();
      scenes_.pop_back();
    }
   break;
   case Result::destruct:
    delete scenes_.back();
    scenes_.pop_back();
   break;
   default: return;
  }
  if (!scenes_.empty() &&
      scenes_.back()->is_what() == SceneKind::game) {
    std::system("cls");
  }
}

} // namespace ttrs
