#include <SDL2/SDL.h>

#include "../../include/interfaces/BreakInterface.hpp"

enum ChoiceBreak {
    save = 1, erase = 2, quit = 3
};
const int MAX_CHOICES_BREAK = 3;
ChoiceBreak currentChoice = save;

/**
 * @brief Handle SDL Events in the menu
 */
void BreakInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_1:
                currentChoice = save;
                break;
            case SDLK_2:
                currentChoice = erase;
                break;
            case SDLK_3:
                currentChoice = quit;
                break;

            case SDLK_TAB:
                currentChoice = (currentChoice < MAX_CHOICES_BREAK) ? static_cast<ChoiceBreak>(static_cast<int>(currentChoice) + 1) : save;
                break;

            case SDLK_RETURN:
                handleRequest();
                break;
        }
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
    breakScreen->drawCurrent(currentChoice);
}

void BreakInterface::handleRequest() {
    if (currentChoice == save) {
        // engine->verifyAndSaveGame();
    }

    if (currentChoice == erase) {
        // engine->eraseSaves();
    }

    if (currentChoice == quit) {
        engine->clean();
    }
}
