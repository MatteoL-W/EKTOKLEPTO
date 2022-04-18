#include <SDL2/SDL.h>

#include "../../include/interfaces/MenuInterface.hpp"

/**
 * @brief Handle SDL Events in the menu
 */
void MenuInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

}

/**
 * @brief Update the menu
 */
void MenuInterface::update() {
    menu->update();
}

/**
 * @brief Render the menu
 */
void MenuInterface::render() {
    SDL_RenderClear(Game::renderer);

    menu->draw();

    SDL_RenderPresent(Game::renderer);
}
