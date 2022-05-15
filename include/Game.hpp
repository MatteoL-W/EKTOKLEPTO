#pragma once

#include "Map.hpp"
#include "Camera.hpp"

const int MAX_LEVELS = 2;

class Game {
public:
    Game();

    ~Game() = default;

    void update();

    void draw();

    Map *getMap() { return currentMap; }

    Camera* getCamera() { return camera; }

private:
    Map *currentMap;

    Camera *camera;

    int level = 1;

    void handleMusicVolume() const;
};
