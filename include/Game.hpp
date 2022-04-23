#pragma once

#include "Map.hpp"

class Game {
public:
    Game();

    ~Game() = default;

    void update();

    void draw();

private:
    Map *currentMap;
};
