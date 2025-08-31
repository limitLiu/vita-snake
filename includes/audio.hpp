#ifndef SNAKE_AUDIO_H
#define SNAKE_AUDIO_H

#include <SDL2/SDL_mixer.h>

class Audio {
public:
    Audio();

    ~Audio();

private:
    Mix_Music *music = nullptr;
};

#endif
