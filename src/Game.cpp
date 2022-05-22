#include <GL/gl.h>
#include "../include/Game.hpp"
#include "../include/tools/Sound.hpp"
#include "../include/tools/save.hpp"

Sound* levelUpSound;
std::string Game::saveEmplacements = "assets/save/save.txt";
int Game::level = 1;

Game::Game() {}

void Game::setMap() {
    if (Game::level == 0) { Game::level = 1; }
    currentMap = new Map(Game::level);
    camera = new Camera(currentMap, currentMap->getMapZoom());
    camera->newLevel(Game::level);

    handleMusicVolume();
    levelUpSound = new Sound("./assets/sounds/level_up.wav");
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        level++;
        currentMap = new Map(level);

        levelUpSound->play();

        camera->setMap(currentMap);
        camera->newLevel(level);
    }

    camera->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
    camera->draw();
}

void Game::handleMusicVolume() {
    Mix_Volume(-1, MIX_MAX_VOLUME / 2);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}
