#pragma once

#include "glm/vec2.hpp"

class Box {
public:
    Box(float p_xCoord1, float p_yCoord1, float p_xCoord2, float p_yCoord2, float p_xMin = 0, float p_xMax = 0,
        float p_yMin = 0, float p_yMax = 0)
            : TLPosition(p_xCoord1, p_yCoord1), BRPosition(p_xCoord2, p_yCoord2), xMin(p_xMin), xMax(p_xMax),
              yMin(p_yMin), yMax(p_yMax) {}

    ~Box();

    void draw();

    glm::vec2 getTLPosition() { return TLPosition; };

    glm::vec2 getBRPosition() { return BRPosition; };

    glm::vec2 getTRPosition() const { return {BRPosition.x, TLPosition.y}; };

    glm::vec2 getBLPosition() const { return {TLPosition.x, BRPosition.y}; };

private:
    glm::vec2 TLPosition;

    glm::vec2 BRPosition;

    float xMin, xMax;
    float yMin, yMax;
    float speed;
};