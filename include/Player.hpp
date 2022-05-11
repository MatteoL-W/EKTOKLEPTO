#pragma once

#include "glm/vec2.hpp"
#include "tools/utils.hpp"

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), BLPositionStart(p_xStart, p_yStart), BLPosition(p_xStart, p_yStart),
              BLPositionEnd(p_xEnd, p_yEnd) {
        setPropsFromType();
    }

    ~Player();

    void draw();

    void drawEndPlace();

    float xSpeed = 0.05;
    float ySpeedUp = 0.18;
    float gravity = 0.05;
    float xAccRight = 0.00;
    float xAccLeft = 0.00;
    float yAccUp = 0.00;
    bool movingRight, movingLeft, doubleJump = false;
    void jump();
    void posUpdate();

    void setStatus(bool p_hasFinished) { hasFinished = p_hasFinished; };

    glm::vec2 getCenteredPosition() const { return {BLPosition.x + width / 2, BLPosition.y + height / 2}; };
    glm::vec2 getCenteredPositionEnd() const { return {BLPositionEnd.x + width / 2, BLPositionEnd.y + height / 2}; };

    glm::vec2 getBLPosition() const { return BLPosition; };
    glm::vec2 getBLPositionStart() const { return BLPositionStart; };
    glm::vec2 getBLPositionEnd() const { return BLPositionEnd; };

private:
    int type;

    glm::vec2 BLPositionStart;
    glm::vec2 BLPosition;
    glm::vec2 BLPositionEnd;

    bool hasFinished = false;

    float width, height;

    float r, g, b;

    void setPropsFromType();
};