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
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        /* Changement de joueur avec 0, 1, 2 ... */
        for (size_t i = 0; i < currentMap->playerCount; i++) {
            if (event.key.keysym.sym == SDLK_KeysFrom1ToMax[i]) {
                currentMap->setCurrentPlayer((int)i);
            }
        }

        // Changement de joueurs avec Tab
        switch (event.key.keysym.sym) {
            case SDLK_TAB:
                currentMap->setCurrentPlayer(currentMap->currentPlayerId + 1);
                break;
        }
    }
}

/**
 * @brief Update the menu
 */
void GameInterface::update() {
    game->update();
}

/**
 * @brief Render the menu
 */
void GameInterface::render() {
    game->draw();
}

