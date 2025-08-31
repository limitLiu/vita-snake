#include "audio.hpp"
#include "game.hpp"
#include <memory>

int main(int argc, char *argv[]) {
  Audio audio;
  Game game;

  while (game.isRunning()) {
    game.render();
    game.handleEvents();
    game.update();
  }
  return 0;
}
