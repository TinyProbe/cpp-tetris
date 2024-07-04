#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <cstddef>
#include <chrono>
#include <string>
#include <vector>

namespace ttrs {

enum class Result : int {
  nothing_to_do,
  construct_game,
  construct_option,
  construct_pause,
  destruct_to_main,
  destruct,
};

enum class Select : int {
  unselectable,
  button,
  setting,
};

enum class SceneKind : int {
  scene,
  menu,
  option,
  game,
  pause,
};

// g_kBlocks[(int)BlockKind::...][0..4] == NxN block texture
enum class BlockKind : int {
  red_Z,
  orange_J,
  yellow_O,
  green_S,
  blue_L,
  purple_T,
  brown_I,
};

// g_kColors[(int)Color::...] == emoticon string
enum class Color : int {
  empty,
  red,
  orange,
  yellow,
  green,
  blue,
  purple,
  brown,
  black,
  white,
  recycle,
  up,
  down,
};

struct GameOption {
  int block_speed;
  int block_speed_min;
  int block_speed_max;
};

class Object;

using ComponentIterator = std::vector<Object *>::iterator;
using Texture = std::vector<std::vector<Color>>;

using Clock = std::chrono::steady_clock;
using Time = std::chrono::time_point<Clock>;
using Duration = std::chrono::duration<long long, std::milli>;
using Milli = std::chrono::milliseconds;

void gotoxy(int x, int y);
void show_console_cursor(bool showFlag);
int __random(int min, int max);
void debug_msg(int x, int y, std::string const &msg);

extern std::size_t const g_kRow;
extern std::size_t const g_kCol;
extern std::size_t const g_kHeight;
extern std::size_t const g_kWidth;

extern std::size_t const g_kTitle_x;
extern std::size_t const g_kTitle_y;
extern std::size_t const g_kGame_x;
extern std::size_t const g_kGame_y;

extern std::size_t const g_kGame_holder_wid;
extern std::size_t const g_kGame_holder_hei;
extern std::size_t const g_kGame_board_wid;
extern std::size_t const g_kGame_board_hei;
extern std::size_t const g_kGame_queue_wid;
extern std::size_t const g_kGame_queue_hei;
extern std::size_t const g_kGame_holder_x;
extern std::size_t const g_kGame_holder_y;
extern std::size_t const g_kGame_board_x;
extern std::size_t const g_kGame_board_y;
extern std::size_t const g_kGame_queue_x;
extern std::size_t const g_kGame_queue_y;

extern std::size_t const g_kOption_width;
extern std::size_t const g_kQueue_limit;
extern std::size_t const g_kBlock_rotate_num;

extern std::size_t const g_kOption_game_speed_default;
extern std::size_t const g_kOption_game_speed_min;
extern std::size_t const g_kOption_game_speed_max;

extern std::string const g_kSelector_button_left;
extern std::string const g_kSelector_button_right;
extern std::string const g_kSelector_setting_left;
extern std::string const g_kSelector_setting_right;
extern std::vector<std::vector<int>> const g_kCoordinates_corrections;
extern std::vector<std::string> const g_kColors;
extern std::vector<std::vector<Texture>> const g_kTextures;

} // namespace ttrs

#endif // TETRIS_TETRIS_H
