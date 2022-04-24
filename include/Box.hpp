#pragma once

#include "glm/vec2.hpp"

class Box {
public:
    Box(float p_xCoord1, float p_yCoord1, float p_xCoord2, float p_yCoord2)
            : topLeftCoordinates(p_xCoord1, p_yCoord1), bottomRightCoordinates(p_xCoord2, p_yCoord2) {}

    ~Box();

    void draw();

private:
    glm::vec2 topLeftCoordinates;

    glm::vec2 bottomRightCoordinates;
};