#include <GL/gl.h>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

Player::~Player() {}

void Player::draw() {
    glColor3f(r, g, b);
    drawRect(xStart, yStart, xStart + width, yStart + height);
}

void Player::drawEndPlace() {
    glColor3f(r, g, b);
    drawRect(xEnd, yEnd, xEnd + width, yEnd + height, false);
}
