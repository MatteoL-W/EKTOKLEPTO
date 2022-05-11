#include <GL/gl.h>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

Player::~Player() {}

void Player::draw() {
    if (!hasFinished) {
        glColor3f(r, g, b);
    } else {
        glColor3f(255, 255, 255);
    }

    drawRect(
            glm::vec2(BLPosition.x, BLPosition.y + height),
            glm::vec2(BLPosition.x + width, BLPosition.y)
    );
}

void Player::drawEndPlace() {
    glColor3f(r, g, b);
    drawRect(
            glm::vec2(BLPositionEnd.x, BLPositionEnd.y + height),
            glm::vec2(BLPositionEnd.x + width, BLPositionEnd.y),
            false
    );
}

void Player::jump() {
    if (yAccUp > 0.0 && !doubleJump){
        yAccUp = 1.00;
        doubleJump = true;
    } else if (yAccUp == 0.0){
        yAccUp = 1.00;
    }
}

void Player::posUpdate() {
    BLPosition.x = BLPosition.x + xSpeed * xAccRight - xSpeed * xAccLeft;
    BLPosition.y = BLPosition.y + ySpeedUp * yAccUp - gravity;

    if (movingRight){
        xAccRight = 1.00;
    } else {
        xAccRight = xAccRight * 0.93;
    }

    if (movingLeft){
        xAccLeft = 1.00;
    } else {
        xAccLeft = xAccLeft * 0.93;
    }

    yAccUp = yAccUp * 0.9;

    if (yAccUp <= 0.05){
        yAccUp = 0;
        doubleJump = false;
    }
}

void Player::setPropsFromType() {
    switch (type) {
        case 1:
            width = 1;
            height = 1;
            r = 0.74;
            g = 0.3;
            b = 0.25;
            break;
        case 2:
            width = 0.5;
            height = 0.5;
            r = 0;
            g = 1;
            b = 0;
            break;
    }
}
