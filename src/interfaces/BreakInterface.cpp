#include <SDL2/SDL.h>

#include "../../include/interfaces/BreakInterface.hpp"

/**
 * @brief Handle SDL Events in the menu
 */
void BreakInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

}

/**
 * @brief Update the menu
 */
void BreakInterface::update() {
    breakScreen->update();
}

/**
 * @brief Render the menu
 */
void BreakInterface::render() {
    breakScreen->draw();
}
