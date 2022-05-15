#pragma once

#include <SDL2/SDL_mixer.h>

class Sound {
public:
    Sound(const char *path)
            : soundChunk(Mix_LoadWAV(path)) {};

    ~Sound() = default;

    void play();

private:
    Mix_Chunk *soundChunk;
};


