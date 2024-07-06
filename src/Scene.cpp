#include <Scene.hpp>
#include <Selector.hpp>
#include <Setting.hpp>
#include <Screen.hpp>

namespace ttrs {

Scene::Scene() {}
Scene::~Scene() {
  for (Object *obj : components_) {
    delete obj;
  }
}

void Scene::render(Screen &screen) const {
  screen.clear();
  for (Object *obj : components_) {
    obj->render(screen);
  }
  screen.output(g_kCol, g_kRow);
}

void Scene::render() {
  for (Object *obj : components_) {
    obj->rebuild();
    obj->render();
  }
}

void Scene::update(Result &result, std::size_t &change) {
  for (Object *obj : components_) {
    obj->update(result, change);
  }
}

void Scene::process(Result &result, std::size_t &change) {
  (void)result;
  (void)change;
}

SceneKind Scene::is_what() const {
  return SceneKind::scene;
}

void Scene::select_up(std::size_t &change) {
  Selector *selector = (Selector *)components_.back();
  ComponentIterator itr = selector->current_select();
  while (itr != components_.begin()) {
    if ((*--itr)->is_selectable() != Select::unselectable) {
      selector->select(itr);
      ++change;
      return;
    }
  }
}

void Scene::select_down(std::size_t &change) {
  Selector *selector = (Selector *)components_.back();
  ComponentIterator itr = selector->current_select();
  while (++itr != components_.end()) {
    if ((*itr)->is_selectable() != Select::unselectable) {
      selector->select(itr);
      ++change;
      return;
    }
  }
}

void Scene::select_exec(Result &result) {
  Selector *selector = (Selector *)components_.back();
  selector->exec(result);
}

void Scene::option_down(std::size_t &change) {
  Selector *selector = (Selector *)components_.back();
  ComponentIterator itr = selector->current_select();
  if ((*itr)->is_selectable() != Select::setting) { return; }
  Setting *setting = (Setting *)*itr;
  if (setting->set_option_value(setting->get_option_value() - 1)) {
    (*itr)->correction(*selector);
    setting->rebuild();
    ++change;
  }
}

void Scene::option_up(std::size_t &change) {
  Selector *selector = (Selector *)components_.back();
  ComponentIterator itr = selector->current_select();
  if ((*itr)->is_selectable() != Select::setting) { return; }
  Setting *setting = (Setting *)*itr;
  if (setting->set_option_value(setting->get_option_value() + 1)) {
    (*itr)->correction(*selector);
    setting->rebuild();
    ++change;
  }
}

} // namespace ttrs
