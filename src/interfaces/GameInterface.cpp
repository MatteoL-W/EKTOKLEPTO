#include <SDL2/SDL.h>

#include "../../include/interfaces/GameInterface.hpp"
#include <glm/gtx/norm.hpp>

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
                glm::vec2 initial = currentMap->getCurrentPlayer()->getCenteredPosition();
                glm::vec2 final = currentMap->getPlayers()[i]->getCenteredPosition();
                currentMap->setCurrentPlayer((int) i);
                camera->setTrajectory(initial, final);
            }
        }

        // Changement de joueurs avec Tab
        switch (event.key.keysym.sym) {
            case SDLK_TAB:
                glm::vec2 initial = currentMap->getCurrentPlayer()->getCenteredPosition();
                currentMap->chooseNextPlayer();
                glm::vec2 final = currentMap->getCurrentPlayer()->getCenteredPosition();
                camera->setTrajectory(initial, final);
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

