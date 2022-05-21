#pragma once

#include "Map.hpp"
#include "Camera.hpp"
#include "Minimap.hpp"

class Game {
public:
    Game();

    ~Game() = default;

    void setMap();

    void update();

    void draw();

    Map *getMap() { return currentMap; }

    Camera* getCamera() { return camera; }

    static std::string saveEmplacements;

    static int level;

private:
    Map *currentMap;

    Camera *camera;

    Minimap *minimap;
};
