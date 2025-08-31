#include "game.hpp"
#include "tile_map.hpp"

Game::Game() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) >= 0) {
    window = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window != nullptr) {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      SDL_JoystickEventState(SDL_ENABLE);
      for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        joystick = SDL_JoystickOpen(i);
      }
    }
  } else {
    isRunning_ = false;
  }

  auto tileMap = TileMap::instance();
  tileMap->init(renderer, 32, 32);
  tileMap->add("app0:/resources/images/grass.png", "grass");
  tileMap->add("app0:/resources/images/snake_head.png", "snake_head");
  tileMap->add("app0:/resources/images/snake_body.png", "snake_body");

  player_ = new Player(100, 100);
  for (int i = 0; i < 100; ++i) {
    player_->grow();
  }

  isRunning_ = true;
}

Game::~Game() {
  delete player_;
  SDL_JoystickClose(joystick);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  sceKernelExitProcess(0);
}


void Game::handleEvents() {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        isRunning_ = false;
        break;
      case SDL_JOYBUTTONDOWN:
        switch (event.jbutton.button) {
          case BUp:
            player_->setDirection(Up);
            break;
          case BDown:
            player_->setDirection(Down);
            break;
          case BLeft:
            player_->setDirection(Left);
            break;
          case BRight:
            player_->setDirection(Right);
            break;
        }
        break;
      default:
        break;
    }
  }
}

void Game::update() {
  player_->update();
}

void Game::render() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  TileMap::instance()->fill("grass", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  player_->render();
  SDL_RenderPresent(renderer);
}
