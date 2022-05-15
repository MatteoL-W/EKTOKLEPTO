#include <GL/gl.h>
#include "../include/Game.hpp"
#include "../include/tools/Sound.hpp"
#include "../include/tools/Music.hpp"

Sound* levelUpSound;
Music* ambianceMusic;

Game::Game() {
    currentMap = new Map(level);
    camera = new Camera(currentMap, currentMap->getMapZoom());

    handleMusicVolume();
    ambianceMusic = new Music("./assets/sounds/ambiance.wav");
    levelUpSound = new Sound("./assets/sounds/level_up.wav");
    ambianceMusic->play(-1);
}

void Game::handleMusicVolume() const {
    Mix_Volume(-1, MIX_MAX_VOLUME / 2);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        level++;
        currentMap = new Map(level);

        levelUpSound->play();

        camera->setMap(currentMap);
        camera->setZoom(currentMap->getMapZoom());
    }

    camera->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
    camera->draw();
}

