#include <SDL2/SDL.h>

#include "../../include/interfaces/MenuInterface.hpp"

enum ChoiceMenu {
    start = 1, load = 2, quit = 3
};
const int MAX_CHOICES_MENU = 3;
ChoiceMenu currentChoice = start;

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
                // start the game
            }

            if ((load.first.x < (float) xMouse && (float) xMouse < load.second.x) &&
                (load.second.y > (float) yMouse && (float) yMouse > load.first.y)) {
                // proposer load
            }

            if ((quit.first.x < (float) xMouse && (float) xMouse < quit.second.x) &&
                (quit.second.y > (float) yMouse && (float) yMouse > quit.first.y)) {
                engine->clean();
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
            glm::vec2(214, 258),
            glm::vec2(642, 305)
    );

    load = std::make_pair(
            glm::vec2(5, 5),
            glm::vec2(10, 10)
    );

    quit = std::make_pair(
            glm::vec2(1, 1),
            glm::vec2(5, 5)
    );
}
