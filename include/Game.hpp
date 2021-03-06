#pragma once

#include "Map.hpp"
#include "Camera.hpp"

class Game {
public:
    Game();

    ~Game() = default;

    void setMap();

    void update();

    void draw();

    Map *getMap() { return currentMap; }

    Camera *getCamera() { return camera; }

    static std::string saveEmplacements;

    static int level;

    bool isEnded() const { return ended; };

private:

    Map *currentMap;

    Camera *camera;

    static void handleMusicVolume();

    bool ended = false;
};
