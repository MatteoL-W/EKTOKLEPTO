#include <GL/gl.h>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

Player::~Player() {}

void Player::draw() {
    glColor3f(r, g, b);
    drawRect(positionStart, positionStartBottomRight);
}

void Player::drawEndPlace() {
    glColor3f(r, g, b);
    drawRect(positionEnd, positionEndBottomRight, false);
}

void Player::setPropsFromType() {
    switch (type) {
        case 1:
            width = 1;
            height = 1;
            r = 0.74;
            g = 0.3;
            b = 0.25;
    }
}
