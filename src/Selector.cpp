#include <Selector.hpp>

namespace ttrs {

Selector::Selector() : Object() {
  pixels_.push_back(std::string());
}
Selector::~Selector() {}

void Selector::exec(Result &result) const {
  (*selected_)->exec(result);
}

void Selector::select(ComponentIterator itr) {
  selected_ = itr;
  (*itr)->correction(*this);
}

ComponentIterator Selector::current_select() const {
  return selected_;
}

} // namespace ttrs
