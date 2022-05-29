#pragma once

#include "glm/vec2.hpp"
#include <glm/gtx/norm.hpp>

class Box {
public:
    Box(float p_xCoord1, float p_yCoord1, float p_xCoord2, float p_yCoord2, float p_xMax = 0, float p_yMax = 0,
        float p_speed = 0.005)
            : TLPosition(p_xCoord1, p_yCoord1), BRPosition(p_xCoord2, p_yCoord2),
              TLInitialPosition(p_xCoord1, p_yCoord1), BRInitialPosition(p_xCoord2, p_yCoord2),
              TLMaxPosition(p_xCoord1 + p_xMax, p_yCoord1 + p_yMax),
              BRMaxPosition(p_xCoord2 + p_xMax, p_yCoord2 + p_yMax),
              TLDestination(TLMaxPosition), direction(glm::normalize(TLDestination - TLPosition)), speed(p_speed) {}

    ~Box() = default;

    void update();

    void draw();

    glm::vec2 getTLPosition() { return TLPosition; };

    glm::vec2 getBRPosition() { return BRPosition; };

    glm::vec2 getTLMaxPosition() { return TLMaxPosition; };

    glm::vec2 getBRMaxPosition() { return BRMaxPosition; };

    glm::vec2 getTRPosition() const { return {BRPosition.x, TLPosition.y}; };

    glm::vec2 getBLPosition() const { return {TLPosition.x, BRPosition.y}; };

    void setTLPosition(glm::vec2 p_TLPosition) { TLPosition = p_TLPosition; };

    void setBRPosition(glm::vec2 p_BRPosition) { BRPosition = p_BRPosition; };

    float getSpeed() const { return speed; };

    float getHorizontalMovement() const { return direction.x * speed; };

    float getVerticalMovement() const { return direction.y * speed; };

    bool isMovable() { return (TLInitialPosition != TLMaxPosition); };

private:
    glm::vec2 TLPosition;
    glm::vec2 BRPosition;

    glm::vec2 TLInitialPosition;
    glm::vec2 BRInitialPosition;

    glm::vec2 TLMaxPosition;
    glm::vec2 BRMaxPosition;

    glm::vec2 TLDestination;

    glm::vec2 direction;
    float speed;
};