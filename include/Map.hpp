#pragma once

#include <iostream>
#include <vector>
#include "Box.hpp"
#include "Player.hpp"

const int MAX_SQUARES = 32;
const int MAX_PLAYERS = 5;

class Map {
public:
    Map();

    ~Map() = default;

    void update();

    void draw();

    size_t boxCount = 0;

    size_t playerCount = 0;

private:
    void loadMapInfo(int idMap);

    void stockMapInfo(std::string pString[3][MAX_SQUARES]);

    int mapWidth, mapHeight;

    std::vector<Box*> boxes;

    std::vector<Player*> players;
};
