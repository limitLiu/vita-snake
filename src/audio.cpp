#include "audio.hpp"

Audio::Audio() {
  if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) >= 0) {
    music = Mix_LoadMUS("app0:/resources/audio/snake.ogg");
    Mix_PlayMusic(music, -1);
  }
}

Audio::~Audio() {
  Mix_FreeMusic(music);
  Mix_Quit();
}
