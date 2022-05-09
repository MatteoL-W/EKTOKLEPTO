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

    void save(const std::string& saveContent);

    void initializeMap();

    Map *getMap() { return currentMap; }

    Camera* getCamera() { return camera; }

private:
    std::string readSave();

    Map *currentMap;

    Camera *camera;

    int level = 1;

    std::string saveEmplacements = "assets/save/save.txt";
};
