#pragma once

#include "Map.hpp"
#include "Camera.hpp"

class Game {
public:
    Game();

    ~Game() = default;

    void setMap(int gameId = -1);

    void update();

    void draw();

    void initializeMap(int gameId);

    Map *getMap() { return currentMap; }

    Camera* getCamera() { return camera; }

    static std::string saveEmplacements;

private:

    Map *currentMap;

    Camera *camera;

    int level = 1;
};
