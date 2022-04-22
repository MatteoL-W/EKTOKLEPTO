#include <SDL2/SDL.h>

#include "../include/Main.hpp"
#include "../include/Engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/gtx/intersect.hpp>

Engine *engine = nullptr;
GLuint idtest;
glm::vec3 o;

int main(int argc, char *argv[]) {
    engine = new Engine();

    while (engine->running()) {
        Uint32 frameStart = SDL_GetTicks();

        engine->refresh();

        // FPS Handle (custom in Main.hpp)
        unsigned int frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}
