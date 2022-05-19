#include <SDL2/SDL.h>

#include "../../include/interfaces/BreakInterface.hpp"

enum ChoiceBreak {
    save = 1, erase = 2, quit = 3
};
const int MAX_CHOICES_BREAK = 3;
ChoiceBreak currentChoiceBreak = save;

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
                currentChoiceBreak = save;
                break;
            case SDLK_2:
                currentChoiceBreak = erase;
                break;
            case SDLK_3:
                currentChoiceBreak = quit;
                break;

            case SDLK_TAB:
                currentChoiceBreak = (currentChoiceBreak < MAX_CHOICES_BREAK) ?
                        static_cast<ChoiceBreak>(static_cast<int>(currentChoiceBreak) + 1) : save;
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
    breakScreen->drawCurrent(currentChoiceBreak);
}

void BreakInterface::handleRequest() {
    if (currentChoiceBreak == save) {
        // engine->verifyAndSaveGame();
    }

    if (currentChoiceBreak == erase) {
        // engine->eraseSaves();
    }

    if (currentChoiceBreak == quit) {
        engine->clean();
    }
}
