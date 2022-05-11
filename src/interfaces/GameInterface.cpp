#include <SDL2/SDL.h>

#include "../../include/interfaces/GameInterface.hpp"

int SDLK_KeysFrom1ToMax[MAX_PLAYERS] = {
        SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5
};

/**
 * @brief Handle SDL Events in the menu
 */
void GameInterface::handleEvents() {
    SDL_Event event = engine->event;
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&event);
    Player* currentPlayer = currentMap->getCurrentPlayer();

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {

        /* Changement de joueur avec 0, 1, 2 ... */
        for (size_t i = 0; i < currentMap->playerCount; i++) {
            if (event.key.keysym.sym == SDLK_KeysFrom1ToMax[i]) {
                currentMap->setCurrentPlayer((int) i);
            }
        }

        switch (event.key.keysym.sym) {
            // Changement de joueurs avec Tab
            case SDLK_TAB:
                currentMap->chooseNextPlayer();
                break;
            case SDLK_r:
                currentMap->restart();
                break;
        }
    }

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

        if (keyState[SDL_SCANCODE_RIGHT]){
            currentPlayer->movingRight = true;
        } else {
            currentPlayer->movingRight = false;
        }

        if (keyState[SDL_SCANCODE_LEFT]){
            currentPlayer->movingLeft = true;
        } else {
            currentPlayer->movingLeft = false;
        }

        if (keyState[SDL_SCANCODE_SPACE]){
            currentPlayer->jump();
        }

    }
}

/**
 * @brief Update the menu
 */
void GameInterface::update() {
    if (game->getMap() != currentMap) {
        currentMap = game->getMap();
    }
    game->update();
}

/**
 * @brief Render the menu
 */
void GameInterface::render() {
    game->draw();
}

