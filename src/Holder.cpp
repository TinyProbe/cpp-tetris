#include <Holder.hpp>
#include <Block.hpp>

#include <algorithm>

namespace ttrs {

Holder::Holder(int x, int y, int hei, int wid, GameOption *go)
    : SelfObject() {
  x_ = x;
  y_ = y;
  texture_.resize(hei, std::vector<Color>(wid, Color::empty));
  for (int i = 0; i < wid; ++i) {
    texture_.front()[i] = Color::white;
    texture_.back()[i] = Color::white;
  }
  for (int i = 0; i < hei; ++i) {
    texture_[i].front() = Color::white;
    texture_[i].back() = Color::white;
  }
  game_option_ = go;
  block_ = nullptr;
}
Holder::~Holder() {}

Block *Holder::swap_block(Block *block) {
  if (block_) {
    int wid = (int)block_->get_texture()[0].size();
    block_->set_x((int)g_kGame_board_x +
                  (int)g_kGame_board_wid - (wid / 2 + wid % 2) * 2);
    block_->set_y((int)g_kGame_board_y);
    block_->time_reset();
  }
  std::swap(block_, block);
  int x = x_ + 2;
  int y = y_ + 1;
  x += 4 - g_kTextures[(int)block_->get_block_kind()][0][0].size();
  if (block_->get_block_kind() != BlockKind::brown_I) { y += 1; }
  block_->set_x(x);
  block_->set_y(y);
  block_->set_rotate(0);
  block_->set_blank(true);
  return block;
}

bool Holder::is_blank() const {
  if (!block_) { return false; }
  return block_->is_blank();
}

void Holder::set_blank(bool is) {
  if (block_) { block_->set_blank(is); }
}

void Holder::render() {
  SelfObject::render();
  if (block_) {
    block_->rebuild();
    block_->render();
  }
}

void Holder::rebuild() {
  pixels_.resize(texture_.size());
  for (int i = 0; i < (int)texture_.size(); ++i) {
    pixels_[i].clear();
    for (int j = 0; j < (int)texture_[i].size(); ++j) {
      pixels_[i] += g_kColors[(int)texture_[i][j]];
    }
  }
}

} // namespace ttrs
