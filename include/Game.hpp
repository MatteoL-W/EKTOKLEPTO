#pragma once

#include "Map.hpp"
#include "Camera.hpp"

class Game {
public:
    Game();

    ~Game() = default;

    void update();

    void draw();

    Map *getMap() { return currentMap; }

private:
    Map *currentMap;

    Camera *camera;
};
