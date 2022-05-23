#pragma once

#include <SDL2/SDL_mixer.h>

class Sound {
public:
    explicit Sound(const char *path)
            : soundChunk(Mix_LoadWAV(path)) {};

    ~Sound() = default;

    void play() { Mix_PlayChannel(-1, soundChunk, false); };

private:
    Mix_Chunk *soundChunk;
};


