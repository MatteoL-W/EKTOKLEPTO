#include <SDL2/SDL.h>

#include "../../include/interfaces/EndInterface.hpp"

/**
 * @brief Handle SDL Events in the menu
 */
void EndInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                break;

            case SDLK_RETURN:
                break;
        }
    }
}

/**
 * @brief Update the menu
 */
void EndInterface::update() {
    end->update();
}

/**
 * @brief Render the menu
 */
void EndInterface::render() {
    end->draw();
}

