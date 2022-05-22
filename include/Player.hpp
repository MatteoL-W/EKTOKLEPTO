#pragma once

#include "glm/vec2.hpp"
#include "tools/utils.hpp"
#include "tools/Image.hpp"

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), BLPositionStart(p_xStart, p_yStart), BLPosition(p_xStart, p_yStart),
              BLPositionEnd(p_xEnd, p_yEnd) {
        setPropsFromType();
    }

    ~Player() = default;

    void draw();

    void drawEndPlace();

    void moveRight();

    void reset() { BLPosition = BLPositionStart; };

    void setStatus(bool p_hasFinished) { hasFinished = p_hasFinished; };

    glm::vec2 getCenteredPosition() const { return {BLPosition.x + width / 2, BLPosition.y + height / 2}; };
    glm::vec2 getCenteredPositionEnd() const { return {BLPositionEnd.x + width / 2, BLPositionEnd.y + height / 2}; };

    glm::vec2 getBLPosition() const { return BLPosition; };
    glm::vec2 getBRPosition() const { glm::vec2 playerBR = BLPosition; playerBR.x = BLPosition.x + width; return playerBR;  };
    glm::vec2 getBLPositionStart() const { return BLPositionStart; };
    glm::vec2 getBLPositionEnd() const { return BLPositionEnd; };

    float getWidth() const { return width; };
    float getHeight() const { return height; };
    float getFixWidth() const { return fixWidth; };
    float getFixHeight() const { return fixHeight; };

    void setMiniMode();

    void unsetMiniMode();

private:
    int type;

    glm::vec2 BLPositionStart;
    glm::vec2 BLPosition;
    glm::vec2 BLPositionEnd;

    float fixWidth, fixHeight;
    float width, height;
    float r, g, b;
    Image* background;

    bool hasFinished = false;

    void setPropsFromType();
};