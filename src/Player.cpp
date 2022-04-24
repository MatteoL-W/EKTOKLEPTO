#include <GL/gl.h>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

Player::~Player() {}

void Player::draw() {
    glColor3f(r, g, b);
    drawRect(positionStart.x, positionStart.y, positionStart.x + width, positionStart.y + height);
}

void Player::drawEndPlace() {
    glColor3f(r, g, b);
    drawRect(positionEnd.x, positionEnd.y, positionEnd.x + width, positionEnd.y + height, false);
}
