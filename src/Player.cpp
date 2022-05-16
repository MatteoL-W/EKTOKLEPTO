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

void Player::moveRight() {
    BLPosition.x += 0.01;
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
        case 3:
            width = 1;
            height = 2;
            r = 1;
            g = 0.5;
            b = 0.2;
            break;
    }
}
