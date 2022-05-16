#pragma once

#include "Map.hpp"
#include "Camera.hpp"

const int MAX_LEVELS = 3;

class Game {
public:
    Game();

    ~Game() = default;

    void setMap(int gameId = -1);

    void update();

    void draw();

    void save(const std::string& saveContent);

    void initializeMap(int gameId);

    Map *getMap() { return currentMap; }

    Camera* getCamera() { return camera; }

private:
    std::string readSave(int saveId);

    Map *currentMap;

    Camera *camera;

    int level = 1;

    std::string saveEmplacements = "assets/save/save.txt";
};
