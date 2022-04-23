#pragma once

#include <iostream>
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

    int boxCount = 0;

    int playerCount = 0;

private:
    void loadMapInfo(int idMap);

    void stockMapInfo(std::string pString[3][MAX_SQUARES]);

    int mapWidth, mapHeight;

    Box *boxes[MAX_SQUARES];

    Player *players[MAX_PLAYERS];
};
