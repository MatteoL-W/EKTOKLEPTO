#pragma once

#include "glm/vec2.hpp"
#include "tools/utils.hpp"

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), TLPositionStart(p_xStart, p_yStart), BLPosition(p_xStart, p_yStart),
              TLPositionEnd(p_xEnd, p_yEnd) {
        setPropsFromType();
        BRPositionStart = glm::vec2(TLPositionStart.x + width, TLPositionStart.y + height);
        BRPositionEnd = glm::vec2(TLPositionEnd.x + width, TLPositionEnd.y + height);
    }

    ~Player();

    void draw();

    void drawEndPlace();

    void moveRight();

    glm::vec2 getCenteredPosition() const { return {BLPosition.x + width / 2, BLPosition.y + height / 2}; };

private:
    int type;

    glm::vec2 TLPositionStart;
    glm::vec2 BRPositionStart;

    glm::vec2 BLPosition;

    glm::vec2 TLPositionEnd;
    glm::vec2 BRPositionEnd;

    float width, height;

    float r, g, b;

    void setPropsFromType();
};