#include <inc/Board.hpp>
#include <inc/Holder.hpp>
#include <inc/Queue.hpp>
#include <inc/Block.hpp>

namespace ttrs {

Board::Board(int x, int y, int hei, int wid, GameOption *go)
    : SelfObject() {
  x_ = x;
  y_ = y;
  texture_.resize(hei, std::vector<Color>(wid, Color::empty));
  for (int i = 0; i < wid; ++i) {
    texture_.back()[i] = Color::white;
  }
  for (int i = 0; i < hei; ++i) {
    texture_[i].front() = Color::white;
    texture_[i].back() = Color::white;
  }
  game_option_ = go;
  queue_ = nullptr;
  holder_ = nullptr;
  block_ = nullptr;
}
Board::~Board() {
  if (block_) { delete block_; }
}

void Board::link_queue(Queue *queue) {
  queue_ = queue;
}

void Board::link_holder(Holder *holder) {
  holder_ = holder;
}

void Board::next_block() {
  if (!block_) { delete block_; }
  block_ = queue_->pop_next();
  if (block_) {
    int wid = (int)block_->get_texture().back().size();
    block_->set_x((int)g_kGame_board_x +
                  (int)g_kGame_board_wid - (wid / 2 + wid % 2) * 2);
    block_->set_y((int)g_kGame_board_y);
    block_->time_reset();
    block_->link_game_option(game_option_);
  }
}

bool Board::rotate() {
  int x = block_->get_x();
  int y = block_->get_y();
  block_->rotate(1);
  for (int i = 0; i < (int)g_kCoordinates_corrections.size(); ++i) {
    block_->set_x(x + g_kCoordinates_corrections[i][0]);
    block_->set_y(y + g_kCoordinates_corrections[i][1]);
    if (check_colision(*block_)) { return true; }
  }
  block_->rotate((int)g_kBlock_rotate_num - 1);
  block_->set_x(x);
  block_->set_y(y);
  return false;
}

bool Board::move_left() {
  block_->set_x(block_->get_x() - 1 * 2);
  if (!check_colision(*block_)) {
    block_->set_x(block_->get_x() + 1 * 2);
    return false;
  }
  return true;
}

bool Board::move_right() {
  block_->set_x(block_->get_x() + 1 * 2);
  if (!check_colision(*block_)) {
    block_->set_x(block_->get_x() - 1 * 2);
    return false;
  }
  return true;
}

bool Board::move_down() {
  block_->set_y(block_->get_y() + 1);
  if (!check_colision(*block_)) {
    block_->set_y(block_->get_y() - 1);
    return false;
  }
  block_->time_reset();
  return true;
}

bool Board::drop_down(Result &result) {
  while (check_colision(*block_)) {
    block_->set_y(block_->get_y() + 1);
  }
  block_->set_y(block_->get_y() - 1);
  write_to(texture_, *block_);
  cleaning();
  if (!is_line_empty(texture_[0]) || !is_line_empty(texture_[1])) {
    result = Result::destruct;
  }
  next_block();
  holder_->set_blank(false);
  return true;
}

bool Board::recycle() {
  if (holder_->is_blank()) { return false; }
  block_ = holder_->swap_block(block_);
  return true;
}

void Board::update(Result &result, std::size_t &change) {
  if (!block_) {
    next_block();
  } else {
    block_->update(result, change);
    if (!check_colision(*block_)) {
      block_->set_y(block_->get_y() - 1);
      write_to(texture_, *block_);
      cleaning();
      if (!is_line_empty(texture_[0]) || !is_line_empty(texture_[1])) {
        result = Result::destruct;
      }
      next_block();
      holder_->set_blank(false);
    }
  }
}

void Board::rebuild() {
  buffer_ = texture_;
  for (int i = 0; i < (int)buffer_.front().size(); ++i) {
    buffer_[0][i] = Color::black;
    buffer_[1][i] = Color::black;
  }
  if (block_) {
    write_preview();
    write_to(buffer_, *block_);
  }
  pixels_.resize(buffer_.size());
  for (int i = 0; i < (int)buffer_.size(); ++i) {
    pixels_[i].clear();
    for (int j = 0; j < (int)buffer_[i].size(); ++j) {
      pixels_[i] += g_kColors[(int)buffer_[i][j]];
    }
  }
}

void Board::write_preview() {
  Block preview = *block_;
  preview.set_blank(true);
  while (check_colision(preview)) {
    preview.set_y(preview.get_y() + 1);
  }
  preview.set_y(preview.get_y() - 1);
  write_to(buffer_, preview);
}

bool Board::check_colision(Block const &block) const {
  Texture const &texture = block.get_texture();
  int xi = (block.get_x() - (int)g_kGame_board_x) / 2;
  int yi = block.get_y() - (int)g_kGame_board_y;
  for (int i = 0; i < (int)texture.size(); ++i) {
    int y = yi + i;
    if (y < 0 || y >= (int)texture_.size()) { continue; }
    for (int j = 0; j < (int)texture[i].size(); ++j) {
      int x = xi + j;
      if (x < 0 || x >= (int)texture_.back().size()) { continue; }
      if ((texture_[y][x] != Color::empty && texture_[y][x] != Color::black) &&
          texture[i][j] != Color::empty) {
        return false;
      }
    }
  }
  return true;
}

void Board::write_to(Texture &to, Block const &block) {
  Texture const &texture = block.get_texture();
  int xi = (block.get_x() - (int)g_kGame_board_x) / 2;
  int yi = block.get_y() - (int)g_kGame_board_y;
  for (int i = 0; i < (int)texture.size(); ++i) {
    int y = yi + i;
    if (y < 0 || y >= (int)to.size()) { continue; }
    for (int j = 0; j < (int)texture[i].size(); ++j) {
      if (texture[i][j] != Color::empty) {
        int x = xi + j;
        if (x < 0 || x >= (int)to.back().size()) { continue; }
        to[y][x] = block.is_blank() ? Color::black : texture[i][j];
      }
    }
  }
}

void Board::cleaning() {
  int l = (int)texture_.size() - 2;
  int r = (int)texture_.size() - 1;
  while (--r > 0) {
    if (!is_line_full(texture_[r])) {
      texture_[l--] = texture_[r];
    }
  }
}

bool Board::is_line_full(std::vector<Color> const &line) const {
  for (int i = 1; i < (int)line.size() - 1; ++i) {
    if (line[i] == Color::empty) {
      return false;
    }
  }
  return true;
}

bool Board::is_line_empty(std::vector<Color> const &line) const {
  for (int i = 1; i < (int)line.size() - 1; ++i) {
    if (line[i] != Color::empty) {
      return false;
    }
  }
  return true;
}

} // namespace ttrs
