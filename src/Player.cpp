#include <GL/gl.h>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

Player::~Player() {}

void Player::draw() {
    glColor3f(r, g, b);
    // Voir si on définit TL et BR ou pas
    drawRect(
            glm::vec2(BLPosition.x, BLPosition.y + height),
            glm::vec2(BLPosition.x + width, BLPosition.y)
    );
}

void Player::drawEndPlace() {
    glColor3f(r, g, b);
    drawRect(TLPositionEnd, BRPositionEnd, false);
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
