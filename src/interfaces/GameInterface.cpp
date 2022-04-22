#include <SDL2/SDL.h>

#include "../../include/interfaces/GameInterface.hpp"

/**
 * @brief Handle SDL Events in the menu
 */
void GameInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

}

/**
 * @brief Update the menu
 */
void GameInterface::update() {
}

/**
 * @brief Render the menu
 */
void GameInterface::render() {
    SDL_RenderClear(Engine::renderer);


    SDL_RenderPresent(Engine::renderer);
}
