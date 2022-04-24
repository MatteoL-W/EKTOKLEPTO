#include <SDL2/SDL.h>

#include "../include/main.hpp"
#include "../include/Engine.hpp"
#include <SDL2/SDL.h>

Engine *engine = nullptr;

int main(int argc, char *argv[]) {
    engine = new Engine();

    while (engine->running()) {
        Uint32 frameStart = SDL_GetTicks();

        engine->refresh();

        // Custom the FPS in Main.hpp
        unsigned int frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}
