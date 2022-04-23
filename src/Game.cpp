#include "../include/Game.hpp"

Game::Game() {
    this->currentMap = new Map();
}

/**
 * @brief Update the game
 */
void Game::update() {
    currentMap->update();
}

/**
 * @brief Draw the game
 */
void Game::draw() {
    currentMap->draw();
}

