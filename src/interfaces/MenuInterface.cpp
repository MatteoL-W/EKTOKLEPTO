#include <SDL2/SDL.h>

#include "../../include/interfaces/MenuInterface.hpp"

enum Choice {
    start = 1, load = 2, quit = 3
};
Choice currentChoice = start;

/**
 * @brief Handle SDL Events in the menu
 */
void MenuInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_1:
                currentChoice = start;
                break;
            case SDLK_2:
                currentChoice = load;
                break;
            case SDLK_3:
                currentChoice = quit;
                break;
        }
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
    menu->draw();
    menu->drawCurrent(currentChoice);
}
