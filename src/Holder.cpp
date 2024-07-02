#include <inc/Holder.hpp>

namespace ttrs {

Holder::Holder(int x, int y, int hei, int wid) : SelfObject() {
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
  game_option_ = nullptr;
  block_ = nullptr;
}
Holder::~Holder() {}

void Holder::link_game_option(GameOption *go) {
  game_option_ = go;
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
