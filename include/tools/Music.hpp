#pragma once

#include <SDL2/SDL_mixer.h>

class Music {
public:
    explicit Music(const char *path)
            : music(Mix_LoadMUS(path)) {};

    ~Music() = default;

    void play(int loops) { Mix_PlayMusic(music, loops); };

    static void stop() { Mix_HaltMusic(); };

private:
    Mix_Music *music;
};


