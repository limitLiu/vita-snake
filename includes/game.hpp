#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>
#include "player.hpp"

enum {
    SCREEN_WIDTH = 960,
    SCREEN_HEIGHT = 544
};

enum CTRL {
    BTriangle = 0,
    BCircle = 1,
    BCross = 2,
    BSquare = 3,

    BL = 4,
    BR = 5,

    BDown = 6,
    BLeft = 7,
    BUp = 8,
    BRight = 9,

    BSelect = 10,
    BStart = 11
};

class Game {
public:
    Game();

    ~Game();

    void render();

    void update();

    void handleEvents();

    [[nodiscard]] bool isRunning() const { return isRunning_; }

private:
    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;

    SDL_Joystick *joystick = nullptr;

    SDL_Event event{};

    Player *player_ = nullptr;

    bool isRunning_ = false;
};

#endif
