#pragma once

#include "glm/vec2.hpp"

class Zone {
public:
    Zone(glm::vec2 p_TL, glm::vec2 p_BR) : TL(p_TL), BR(p_BR) {};

    ~Zone() = default;

    void draw();

    bool contains(glm::vec2 center);

private:
    glm::vec2 TL;
    glm::vec2 BR;
};