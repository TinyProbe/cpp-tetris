#include <inc/tetris.h>

#include <windows.h>
#include <iostream>
#include <random>

namespace ttrs {

void gotoxy(int x, int y) {
  COORD p = { (short)x, (short)y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void show_console_cursor(bool showFlag) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = showFlag;
  SetConsoleCursorInfo(out, &cursorInfo);
}

int __random(int min, int max) {
  static std::mt19937 gen((std::random_device())());
  return (std::uniform_int_distribution<int>(min, max))(gen);
}

void debug_msg(int x, int y, std::string const &msg) {
  gotoxy(x, y);
  std::cout << msg << std::flush;
}

std::size_t const g_kRow = 0;
std::size_t const g_kCol = 0;
std::size_t const g_kHeight = 28;
std::size_t const g_kWidth = 48 * 2;

std::size_t const g_kTitle_x = 10;
std::size_t const g_kTitle_y = 2;

std::size_t const g_kGame_x = g_kRow + 4 * 2;
std::size_t const g_kGame_y = g_kCol + 4;

std::size_t const g_kGame_holder_wid = 6;
std::size_t const g_kGame_holder_hei = 6;
std::size_t const g_kGame_board_wid = 12;
std::size_t const g_kGame_board_hei = 24;
std::size_t const g_kGame_queue_wid = 6;
std::size_t const g_kGame_queue_hei = 22;

std::size_t const g_kGame_holder_x = g_kGame_x + 0;
std::size_t const g_kGame_holder_y = g_kGame_y + 0;
std::size_t const g_kGame_board_x = g_kGame_holder_x + (g_kGame_holder_wid * 2);
std::size_t const g_kGame_board_y = g_kGame_y - 2;
std::size_t const g_kGame_queue_x = g_kGame_board_x + (g_kGame_board_wid * 2);
std::size_t const g_kGame_queue_y = g_kGame_y + 0;

std::size_t const g_kOption_width = 20;
std::size_t const g_kQueue_limit = 5;
std::size_t const g_kBlock_rotate_num = 4;

std::size_t const g_kOption_game_speed_default = 10;
std::size_t const g_kOption_game_speed_min = 1;
std::size_t const g_kOption_game_speed_max = 20;

std::string const g_kSelector_button_left = "<";
std::string const g_kSelector_button_right = ">";
std::string const g_kSelector_setting_left = "-";
std::string const g_kSelector_setting_right = "+";
std::vector<std::string> const g_kColors = {
  "  ", "🟥", "🟧", "🟨",
  "🟩", "🟦", "🟪", "🟫",
  "🔳", "🔲", "🔜", "🔄",
  "🔼", "🔽", "🏹",
};
std::vector<std::vector<Texture>> const g_kTextures = {
  { // red_Z
    {
      { Color::red, Color::red, Color::empty, },
      { Color::empty, Color::red, Color::red, },
      { Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::empty, Color::red, },
      { Color::empty, Color::red, Color::red, },
      { Color::empty, Color::red, Color::empty, },
    }, {
      { Color::empty, Color::empty, Color::empty, },
      { Color::red, Color::red, Color::empty, },
      { Color::empty, Color::red, Color::red, },
    }, {
      { Color::empty, Color::red, Color::empty, },
      { Color::red, Color::red, Color::empty, },
      { Color::red, Color::empty, Color::empty, },
    },
  }, { // orange_L
    {
      { Color::empty, Color::empty, Color::orange, },
      { Color::orange, Color::orange, Color::orange, },
      { Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::orange, Color::empty, },
      { Color::empty, Color::orange, Color::empty, },
      { Color::empty, Color::orange, Color::orange, },
    }, {
      { Color::empty, Color::empty, Color::empty, },
      { Color::orange, Color::orange, Color::orange, },
      { Color::orange, Color::empty, Color::empty, },
    }, {
      { Color::orange, Color::orange, Color::empty, },
      { Color::empty, Color::orange, Color::empty, },
      { Color::empty, Color::orange, Color::empty, },
    },
  }, { // yellow_O
    {
      { Color::yellow, Color::yellow, },
      { Color::yellow, Color::yellow, },
    }, {
      { Color::yellow, Color::yellow, },
      { Color::yellow, Color::yellow, },
    }, {
      { Color::yellow, Color::yellow, },
      { Color::yellow, Color::yellow, },
    }, {
      { Color::yellow, Color::yellow, },
      { Color::yellow, Color::yellow, },
    },
  }, { // green_S
    {
      { Color::empty, Color::green, Color::green, },
      { Color::green, Color::green, Color::empty, },
      { Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::green, Color::empty, },
      { Color::empty, Color::green, Color::green, },
      { Color::empty, Color::empty, Color::green, },
    }, {
      { Color::empty, Color::empty, Color::empty, },
      { Color::empty, Color::green, Color::green, },
      { Color::green, Color::green, Color::empty, },
    }, {
      { Color::green, Color::empty, Color::empty, },
      { Color::green, Color::green, Color::empty, },
      { Color::empty, Color::green, Color::empty, },
    },
  }, { // blue_J
    {
      { Color::blue, Color::empty, Color::empty, },
      { Color::blue, Color::blue, Color::blue, },
      { Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::blue, Color::blue, },
      { Color::empty, Color::blue, Color::empty, },
      { Color::empty, Color::blue, Color::empty, },
    }, {
      { Color::empty, Color::empty, Color::empty, },
      { Color::blue, Color::blue, Color::blue, },
      { Color::empty, Color::empty, Color::blue, },
    }, {
      { Color::empty, Color::blue, Color::empty, },
      { Color::empty, Color::blue, Color::empty, },
      { Color::blue, Color::blue, Color::empty, },
    },
  }, { // purple_T
    {
      { Color::empty, Color::purple, Color::empty, },
      { Color::purple, Color::purple, Color::purple, },
      { Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::purple, Color::empty, },
      { Color::empty, Color::purple, Color::purple, },
      { Color::empty, Color::purple, Color::empty, },
    }, {
      { Color::empty, Color::empty, Color::empty, },
      { Color::purple, Color::purple, Color::purple, },
      { Color::empty, Color::purple, Color::empty, },
    }, {
      { Color::empty, Color::purple, Color::empty, },
      { Color::purple, Color::purple, Color::empty, },
      { Color::empty, Color::purple, Color::empty, },
    },
  }, { // brown_I
    {
      { Color::empty, Color::empty, Color::empty, Color::empty, },
      { Color::brown, Color::brown, Color::brown, Color::brown, },
      { Color::empty, Color::empty, Color::empty, Color::empty, },
      { Color::empty, Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::empty, Color::brown, Color::empty, },
      { Color::empty, Color::empty, Color::brown, Color::empty, },
      { Color::empty, Color::empty, Color::brown, Color::empty, },
      { Color::empty, Color::empty, Color::brown, Color::empty, },
    }, {
      { Color::empty, Color::empty, Color::empty, Color::empty, },
      { Color::empty, Color::empty, Color::empty, Color::empty, },
      { Color::brown, Color::brown, Color::brown, Color::brown, },
      { Color::empty, Color::empty, Color::empty, Color::empty, },
    }, {
      { Color::empty, Color::brown, Color::empty, Color::empty, },
      { Color::empty, Color::brown, Color::empty, Color::empty, },
      { Color::empty, Color::brown, Color::empty, Color::empty, },
      { Color::empty, Color::brown, Color::empty, Color::empty, },
    },
  },
};

} // namespace ttrs
