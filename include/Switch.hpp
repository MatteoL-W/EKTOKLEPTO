#pragma once

#include <vector>
#include "glm/vec2.hpp"
#include "Zone.hpp"

class Switch {
public:
    Switch(int p_type, float p_x, float p_y):type(p_type), x(p_x), y(p_y) {};

    ~Switch() = default;

    void update();

    void draw();

    void insertZone(glm::vec2 BL, glm::vec2 TR);

private:
    int type;
    float x, y;

    std::vector<Zone*> zones;
};
