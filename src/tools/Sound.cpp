#include "../include/tools/Sound.hpp"

void Sound::play() {
    Mix_PlayChannel(-1, soundChunk, false);
}