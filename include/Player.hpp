#pragma once

#include "glm/vec2.hpp"

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), positionStart(p_xStart, p_yStart), positionEnd(p_xEnd, p_yEnd) {
        setPropsFromType();
        positionStartBottomRight = glm::vec2(positionStart.x + width, positionStart.y + height);
        positionEndBottomRight = glm::vec2(positionEnd.x + width, positionEnd.y + height);
    }

    ~Player();

    void draw();

    void drawEndPlace();

private:
    int type;

    glm::vec2 positionStart;
    glm::vec2 positionStartBottomRight;

    glm::vec2 positionEnd;
    glm::vec2 positionEndBottomRight;

    float width, height;

    float r, g, b;

    void setPropsFromType();
};