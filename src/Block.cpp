#include <inc/Block.hpp>

#include <iostream>

namespace ttrs {

Block::Block(int x, int y, BlockKind block_kind, bool is_blank)
    : SelfObject() {
  x_ = x;
  y_ = y;
  block_kind_ = block_kind;
  is_blank_ = is_blank;
  rotate_ = 0;
  time_ = Clock::now();
  game_option_ = nullptr;
}
Block::~Block() {}

void Block::update(Result &result, std::size_t &change) {
  (void)result;
  Time now = Clock::now();
  Duration diff = std::chrono::duration_cast<Milli>(now - time_);
  std::size_t max_time = g_kOption_game_speed_max * 50;
  std::size_t need_time = max_time - game_option_->block_speed * 50;
  if (diff >= Milli(need_time)) {
    time_ = now;
    ++y_;
    ++change;
  }
}

void Block::link_game_option(GameOption *go) {
  game_option_ = go;
}

void Block::rebuild() {
  Texture const &texture = get_texture();
  pixels_.resize(texture.size());
  for (int i = 0; i < (int)texture.size(); ++i) {
    pixels_[i].clear();
    for (int j = 0; j < (int)texture[i].size(); ++j) {
      if (is_blank_) {
        pixels_[i] += texture[i][j] != Color::empty ?
            g_kColors[(int)Color::black] : g_kColors[(int)Color::empty];
      } else {
        pixels_[i] += g_kColors[(int)texture[i][j]];
      }
    }
  }
}

BlockKind Block::get_block_kind() const {
  return block_kind_;
}

Texture const &Block::get_texture() const {
  return g_kTextures[(int)block_kind_][rotate_];
}

bool Block::is_blank() const {
  return is_blank_;
}

void Block::set_blank(bool blank) {
  is_blank_ = blank;
}

void Block::rotate(std::size_t time) {
  rotate_ += time;
  rotate_ %= g_kBlock_rotate_num;
}

void Block::time_reset() {
  time_ = Clock::now();
}

} // namespace ttrs
