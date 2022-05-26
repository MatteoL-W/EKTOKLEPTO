#include <SDL2/SDL.h>

#include "../../include/interfaces/MenuInterface.hpp"

enum ChoiceMenu {
    start = 1, openSaveManager, quit
};
const int MAX_CHOICES_MENU = 3;
ChoiceMenu currentChoiceMenu = start;

/**
 * @brief Handle SDL Events in the menu
 */
void MenuInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);

            std::cout << xMouse << " " << yMouse << std::endl;

            if ((start.first.x < (float) xMouse && (float) xMouse < start.second.x) &&
                (start.second.y > (float) yMouse && (float) yMouse > start.first.y)) {
                engine->startGame();
            }

            if ((load.first.x < (float) xMouse && (float) xMouse < load.second.x) &&
                (load.second.y > (float) yMouse && (float) yMouse > load.first.y)) {
                engine->openSaveManager(this);
            }

            if ((quit.first.x < (float) xMouse && (float) xMouse < quit.second.x) &&
                (quit.second.y > (float) yMouse && (float) yMouse > quit.first.y)) {
                engine->setRunning(false);
            }

            break;
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
}

void MenuInterface::setButtonCoordinates() {
    start = std::make_pair(
            glm::vec2(121, 242),
            glm::vec2(282, 300)
    );

    load = std::make_pair(
            glm::vec2(133, 322),
            glm::vec2(441, 376)
    );

    quit = std::make_pair(
            glm::vec2(129, 399),
            glm::vec2(325, 448)
    );
}
