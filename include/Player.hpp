#pragma once

#include <vector>
#include "../include/Box.hpp"
#include "glm/vec2.hpp"
#include "tools/utils.hpp"
#include "tools/Image.hpp"
#include "tools/Sound.hpp"

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), BLPositionStart(p_xStart, p_yStart), BLPosition(p_xStart, p_yStart),
              BLPositionEnd(p_xEnd, p_yEnd) {
        setPropsFromType();
        jumpSound = new Sound("./assets/sounds/jump.wav");
    }

    ~Player() = default;

    void draw();

    void drawGhost();

    void drawEndPlace();

    void jump();

    void posUpdate();

    void reset() {
        BLPosition = BLPositionStart;
        hasFinished = false;
    };

    void setStatus(bool p_hasFinished) { hasFinished = p_hasFinished; };

    bool getStatus() const { return hasFinished; };

    void setBoxes(std::vector<Box *> p_boxes) { nearBoxes = p_boxes; };

    void setPlayers(std::vector<Player *> p_players) { otherPlayers = p_players; };

    void setInactive();

    void removeCurrentFromArray(size_t id);

    void setMovingRight(bool right) { movingRight = right; };

    void setMovingLeft(bool left) { movingLeft = left; };

    glm::vec2 getCenteredPosition() const { return {BLPosition.x + width / 2, BLPosition.y + height / 2}; };

    glm::vec2 getCenteredPositionEnd() const { return {BLPositionEnd.x + width / 2, BLPositionEnd.y + height / 2}; };

    glm::vec2 getBLPosition() const { return BLPosition; };

    glm::vec2 getBRPosition() const {
        glm::vec2 playerBR = BLPosition;
        playerBR.x = BLPosition.x + width;
        return playerBR;
    };

    glm::vec2 getBLPositionStart() const { return BLPositionStart; };

    glm::vec2 getBLPositionEnd() const { return BLPositionEnd; };

    glm::vec2 getTLPosition() const { return {BLPosition.x, BLPosition.y + height}; };

    glm::vec2 getTRPosition() const { return {BLPosition.x + width, BLPosition.y + height}; };

    float getWidth() const { return width; };

    float getHeight() const { return height; };

    float getFixWidth() const { return fixWidth; };

    float getFixHeight() const { return fixHeight; };

    float getCurrentChanges() const { return currentChanges; };

    void setMaxiMode();

    void setMiniMode();

    void unsetMaxiMode();

    void unsetMiniMode();

    void setWarpedGravity();

    void unsetWarpedGravity();

    void setSuperJumpMode() { superJump = true; };

    void unsetSuperJumpMode() { superJump = false; };

private:
    int type;
    int currentChanges;

    glm::vec2 BLPositionStart;
    glm::vec2 BLPosition;
    glm::vec2 BLPositionEnd;

    float fixWidth, fixHeight;
    float width, height;
    float r, g, b;
    Image *background;
    Image *ghost;

    const float xMaxSpeed = 0.14;
    float yMaxSpeedUp = 0.55;
    float gravity = 0.15;
    float xAccRight = 0.00;
    float xAccLeft = 0.00;
    float yAccUp = 0.00;
    float gravityAcc = 1.00;
    float xSpeed, ySpeed, xSpeedMod, ySpeedMod;
    float savedBPx, savedBPy;
    bool movingRight, movingLeft = false;
    bool hasTouchedGround = false;
    bool toJump = false;
    int noJumpCounter = 2;
    int hasJumped = 0;

    // Zone effects
    bool warpedGravity = false;
    bool superJump = true;

    std::vector<Box *> nearBoxes;
    std::vector<Player *> otherPlayers;

    bool collisionBottom, collisionLeft, collisionRight, collisionTop = false;

    void checkCollisions();

    bool isContained(float subject, float limitA, float limitB);

    bool hasFinished = false;

    void setPropsFromType();

    Sound *jumpSound;
};