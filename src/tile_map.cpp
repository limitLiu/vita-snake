#include "tile_map.hpp"
#include <SDL2/SDL_image.h>

TileMap *TileMap::_instance = nullptr;

bool TileMap::add(const std::string &filePath, const std::string &id) {
  SDL_Surface *temp = IMG_Load(filePath.c_str());
  if (temp == nullptr) {
    return false;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, temp);
  if (texture == nullptr) {
    return false;
  }

  SDL_FreeSurface(temp);
  tiles_[id] = texture;
  return true;
}

void TileMap::render(const std::string &id, int x, int y) {
  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = tileW_;
  src.h = tileH_;

  dest.x = x;
  dest.y = y;
  dest.w = tileW_;
  dest.h = tileH_;

  SDL_RenderCopyEx(renderer_, tiles_[id], &src, &dest, 0, nullptr, SDL_FLIP_NONE);
}

void TileMap::fill(const std::string &id, int x, int y, int w, int h) {
  for (int currentX = x; currentX < w; currentX += tileW_) {
    for (int currentY = y; currentY < h; currentY += tileH_) {
      render(id, currentX, currentY);
    }
  }
}

void TileMap::init(SDL_Renderer *renderer, int tileW, int tileH) {
  renderer_ = renderer;
  tileW_ = tileW;
  tileH_ = tileH;
}

TileMap::~TileMap() = default;
