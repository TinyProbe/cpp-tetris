#include <inc/Game.hpp>
#include <inc/Holder.hpp>
#include <inc/Board.hpp>
#include <inc/Queue.hpp>
#include <inc/Block.hpp>

#include <conio.h>

namespace ttrs {

Game::Game(GameOption *go)
    : Scene(), game_option_(go) {
  Holder *holder = new Holder(g_kGame_holder_x, g_kGame_holder_y,
                              g_kGame_holder_hei, g_kGame_holder_wid);
  Queue *queue = new Queue(g_kGame_queue_x, g_kGame_queue_y, g_kQueue_limit);
  Board *board = new Board(g_kGame_board_x, g_kGame_board_y,
                           g_kGame_board_hei, g_kGame_board_wid);

  holder->link_game_option(go);
  queue->link_game_option(go);
  board->link_game_option(go);
  board->link_holder(holder);
  board->link_queue(queue);

  components_.push_back(holder);
  components_.push_back(queue);
  components_.push_back(board);
}
Game::~Game() {}

void Game::process(Result &result, std::size_t &change) {
  if (!_kbhit()) { return; }

  int c = _getch();
  switch (c) {
   case 0: case 224:
    c = _getch();
    switch (c) {
     case 72: // ^
      rotate(change); break;
     case 75: // <
      left(change); break;
     case 77: // >
      right(change); break;
     case 80: // v
      down(change); break;
     default: break;
    } break;
   case 13: case 32: // enter, space
    drop(result, change); break;
   case 27: // esc
    result = Result::construct_pause;
    break;
   default: break;
  }
}

SceneKind Game::is_what() const {
  return SceneKind::game;
}

void Game::rotate(std::size_t &change) {
  Board *board = (Board *)components_.back();
  if (board->rotate()) { ++change; }
}

void Game::left(std::size_t &change) {
  Board *board = (Board *)components_.back();
  if (board->move_left()) { ++change; }
}

void Game::right(std::size_t &change) {
  Board *board = (Board *)components_.back();
  if (board->move_right()) { ++change; }
}

void Game::down(std::size_t &change) {
  Board *board = (Board *)components_.back();
  if (board->move_down()) { ++change; }
}

void Game::drop(Result &result, std::size_t &change) {
  Board *board = (Board *)components_.back();
  if (board->drop_down(result)) { ++change; }
}

} // namespace ttrs
