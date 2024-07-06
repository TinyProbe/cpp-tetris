#include <Queue.hpp>
#include <Block.hpp>

namespace ttrs {

Queue::Queue(int x, int y, std::size_t limit, GameOption *go)
    : SelfObject() {
  x_ = x;
  y_ = y;
  limit_ = limit;
  std::size_t hei = 2 + 4 * limit;
  std::size_t wid = 2 + 4;
  texture_.resize(hei, std::vector<Color>(wid, Color::empty));
  for (std::size_t i = 0; i < wid; ++i) {
    texture_.front()[i] = Color::white;
    texture_.back()[i] = Color::white;
  }
  for (std::size_t i = 0; i < hei; ++i) {
    texture_[i].front() = Color::white;
    texture_[i].back() = Color::white;
  }
  game_option_ = go;
}
Queue::~Queue() {
  while (queue_.size() > 0) {
    delete queue_.front();
    queue_.pop_front();
  }
}

void Queue::update(Result &result, std::size_t &change) {
  (void)result;
  BlockKind random_block;
  while (queue_.size() < limit_) {
    do {
      random_block = (BlockKind)__random((int)BlockKind::red_Z,
                                         (int)BlockKind::brown_I);
    } while (queue_.size() > 0 && queue_.back()->get_block_kind() == random_block);
    int x = x_ + 2;
    int y = y_ + 1 + (4 * queue_.size());
    x += 4 - g_kTextures[(int)random_block][0][0].size();
    if (random_block != BlockKind::brown_I) { y += 1; }
    queue_.push_back(new Block(x, y, random_block, false));
    ++change;
  }
}

void Queue::render() {
  SelfObject::render();
  for (Block *block : queue_) {
    block->rebuild();
    block->render();
  }
}

void Queue::rebuild() {
  pixels_.resize(texture_.size());
  for (int i = 0; i < (int)texture_.size(); ++i) {
    pixels_[i].clear();
    for (int j = 0; j < (int)texture_[i].size(); ++j) {
      pixels_[i] += g_kColors[(int)texture_[i][j]];
    }
  }
}

Block *Queue::pop_next() {
  if (queue_.empty()) { return nullptr; }
  Block *front = queue_.front();
  queue_.pop_front();
  for (Block *block : queue_) {
    block->set_y(block->get_y() - 4);
  }
  return front;
}

} // namespace ttrs
