#pragma once

#include <iostream>
#include "Box.hpp"

const int MAX_SQUARES = 32;

class Map {
public:
    Map();

    ~Map() = default;

    void update();

    void draw();

    int boxCount = 0;

private:
    void loadMapInfo(int idMap);

    void stockMapInfo(std::string pString[3][MAX_SQUARES]);

    int mapWidth, mapHeight;

    Box* boxes[MAX_SQUARES];
};
