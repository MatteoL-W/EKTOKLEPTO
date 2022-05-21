#include <SDL2/SDL.h>

#include "../../include/interfaces/BreakInterface.hpp"

enum ChoiceBreak {
    resume = 1, save, erase, quit
};
const int MAX_CHOICES_BREAK = 4;
ChoiceBreak currentChoiceBreak = resume;

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
                currentChoiceBreak = resume;
                break;
            case SDLK_2:
                currentChoiceBreak = save;
                break;
            case SDLK_3:
                currentChoiceBreak = erase;
                break;
            case SDLK_4:
                currentChoiceBreak = quit;
                break;

            case SDLK_TAB:
                currentChoiceBreak = (currentChoiceBreak < MAX_CHOICES_BREAK) ?
                        static_cast<ChoiceBreak>(static_cast<int>(currentChoiceBreak) + 1) : resume;
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
    breakScreen->update(currentChoiceBreak);
}

/**
 * @brief Render the menu
 */
void BreakInterface::render() {
    breakScreen->draw();
    breakScreen->drawCurrent();
}

void BreakInterface::handleRequest() {
    if (currentChoiceBreak == resume) {
        engine->resumeGame();
    }

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
