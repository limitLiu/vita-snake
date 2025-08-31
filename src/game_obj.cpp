#include "game_obj.hpp"
#include "tile_map.hpp"

void GameObj::load(std::string texture, double x, double y) {
  x_ = x;
  y_ = y;
  texture_ = std::move(texture);
}

void GameObj::render() {
  for (auto child : children) {
    child->render();
  }
  TileMap::instance()->render(texture_, static_cast<int>(round(getX())), static_cast<int>(round(getY())));
}

void GameObj::add(GameObj *child) {
  this->children.push_back(child);
  child->parent = this;
}

void GameObj::update() {
  if (lastUpdate_ == 0) {
    lastUpdate_ = SDL_GetTicks();
  }
  for (auto child : children) {
    child->update();
  }

  auto currentTime = SDL_GetTicks();
  timeDelta_ = (currentTime - lastUpdate_) / 1000.0;
  lastUpdate_ = currentTime;
}

double GameObj::distanceTo(GameObj *other) {
  return distanceTo(other->getX(), other->getY());
}

double GameObj::distanceTo(double x, double y) {
  return sqrt(pow(getX() - x, 2) + pow(getY() - y, 2));
}

// clean resource
GameObj::~GameObj() = default;
