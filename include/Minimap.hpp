#pragma once

#include <GL/glu.h>
#include "Engine.hpp"
#include "Map.hpp"

class Minimap {
public:
    explicit Minimap(Map *p_map)
            : map(p_map){};

    ~Minimap() = default;

    void update();

    void draw();

    void setMap(Map* newMap) { map = newMap; };


private:
    Map *map;
};
