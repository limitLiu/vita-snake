#ifndef SNAKE_TILE_MAP_H
#define SNAKE_TILE_MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <map>
#include <string>

class TileMap {
public:
    static TileMap *instance() {
      if (_instance == nullptr) {
        _instance = new TileMap();
      }
      return _instance;
    }

    void init(SDL_Renderer *renderer, int tileW, int tileH);

    bool add(const std::string &filePath, const std::string &id);

    void render(const std::string &id, int x, int y);

    void fill(const std::string &id, int x, int y, int w, int h);

    ~TileMap();

private:
    static TileMap *_instance;

    TileMap() = default;

    SDL_Renderer *renderer_ = nullptr;
    std::map<std::string, SDL_Texture *> tiles_;

    int tileW_ = 0;
    int tileH_ = 0;
};

#endif
