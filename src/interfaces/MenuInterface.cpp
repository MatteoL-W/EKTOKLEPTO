#include <SDL2/SDL.h>

#include "../../include/interfaces/MenuInterface.hpp"

/**
 * @brief Handle SDL Events in the menu
 */
void MenuInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
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
    SDL_RenderClear(Engine::renderer);

    menu->draw();

    //SDL_RenderPresent(Engine::renderer);
}
