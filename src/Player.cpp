#include <GL/gl.h>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"
#include <iostream>

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

bool Player::isContained(float subject, float limitA, float limitB){
    if (limitA > limitB) {
        return subject >= limitB && subject <= limitA;
    }
    return subject >= limitA && subject <= limitB;
}

void Player::checkCollisions() {
    collisionBottom = false;
    collisionLeft = false;
    collisionRight = false;
    collisionTop = false;

    size_t i = 0;
    while (i < closeBoxes.size()) {  // for each box close to the player

        // check bottom player / top box collision
        if ( ( ( isContained(BLPosition.x, closeBoxes[i]->getBLPosition().x, closeBoxes[i]->getBRPosition().x)
        || isContained(BLPosition.x + width, closeBoxes[i]->getBLPosition().x, closeBoxes[i]->getBRPosition().x) )
        && isContained(BLPosition.y, closeBoxes[i]->getTLPosition().y - 0.2f, closeBoxes[i]->getTLPosition().y) )
        || ( (isContained(closeBoxes[i]->getBLPosition().x, BLPosition.x, BLPosition.x + width)
        || isContained(closeBoxes[i]->getBRPosition().x, BLPosition.x, BLPosition.x + width))
        && isContained(closeBoxes[i]->getTLPosition().y, BLPosition.y, BLPosition.y + 0.2f) ) )
        {
            BLPosition.y = closeBoxes[i]->getTLPosition().y;
            collisionBottom = true;
            hasJumped = false;
            hasDoubleJumped = false;
        } else {
            collisionBottom = false;
        }

        // check top player / bottom box collision
        if ( ( ( isContained(BLPosition.x, closeBoxes[i]->getBLPosition().x, closeBoxes[i]->getBRPosition().x)
        || isContained(BLPosition.x + width, closeBoxes[i]->getBLPosition().x, closeBoxes[i]->getBRPosition().x) )
        && isContained(BLPosition.y + height, closeBoxes[i]->getBLPosition().y,closeBoxes[i]->getBLPosition().y + 0.2f) )
        || ( (isContained(closeBoxes[i]->getBLPosition().x, BLPosition.x, BLPosition.x + width)
        || isContained(closeBoxes[i]->getBRPosition().x, BLPosition.x, BLPosition.x + width))
        && isContained(closeBoxes[i]->getBLPosition().y, BLPosition.y + height - 0.2f, BLPosition.y + height) ) )
        {
            BLPosition.y = closeBoxes[i]->getBLPosition().y - height;
            collisionTop = true;
            yAccUp -= 0.25;
        } else {
            collisionTop = false;
        }

        // check left player / right box collision
        if ( ( ( isContained(BLPosition.y + height, closeBoxes[i]->getBLPosition().y, closeBoxes[i]->getTLPosition().y)
        || isContained(BLPosition.y, closeBoxes[i]->getBLPosition().y, closeBoxes[i]->getTLPosition().y) )
        && isContained(BLPosition.x, closeBoxes[i]->getBRPosition().x - 0.2f, closeBoxes[i]->getBRPosition().x) )
        || ( (isContained(closeBoxes[i]->getBLPosition().y, BLPosition.y, BLPosition.y + height)
        || isContained(closeBoxes[i]->getTLPosition().y, BLPosition.y, BLPosition.y + height))
        && isContained(closeBoxes[i]->getBRPosition().x, BLPosition.x, BLPosition.x + 0.2f) ) )
        {
            BLPosition.x = closeBoxes[i]->getBRPosition().x;
            collisionLeft = true;
        } else {
            collisionLeft = false;
        }

        // check right player / left box collision
        if ( ( ( isContained(BLPosition.y + height, closeBoxes[i]->getBLPosition().y, closeBoxes[i]->getTLPosition().y)
        || isContained(BLPosition.y, closeBoxes[i]->getBLPosition().y, closeBoxes[i]->getTLPosition().y) )
        && isContained(BLPosition.x + width, closeBoxes[i]->getBLPosition().x, closeBoxes[i]->getBLPosition().x + 0.2f) )
        || ( (isContained(closeBoxes[i]->getBLPosition().y, BLPosition.y, BLPosition.y + height)
        || isContained(closeBoxes[i]->getTLPosition().y, BLPosition.y, BLPosition.y + height))
        && isContained(closeBoxes[i]->getBLPosition().x, BLPosition.x + width, BLPosition.x + width - 0.2f) ) )
        {
            BLPosition.x = closeBoxes[i]->getBLPosition().x - width;
            collisionRight = true;
        } else {
            collisionRight = false;
        }

        i++;
    }
}

void Player::jump() {
    if (hasJumped && !hasDoubleJumped){
        yAccUp = 1.00;
        hasDoubleJumped = true;
        // walljump to right
        if (collisionLeft){
            xAccLeft = 0.0;
            xAccRight = 1.50;
        }
        // walljump to left
        if (collisionRight){
            xAccRight = 0.0;
            xAccLeft = 1.50;
        }
    } else if (!hasJumped){
        yAccUp = 1.00;
        hasJumped = true;
    }
}

void Player::posUpdate() {

    // Updating position according to speed and acceleration
    BLPosition.x = BLPosition.x + xMaxSpeed * xAccRight - xMaxSpeed * xAccLeft;
    BLPosition.y = BLPosition.y + yMaxSpeedUp * yAccUp - gravity;

    // If arrow is pushed, max speed in that direction, else, speed is decreasing
    if (movingRight){
        xAccRight = 1.00;
    } else {
        xAccRight = xAccRight * 0.9f;
    }

    if (movingLeft){
        xAccLeft = 1.00;
    } else {
        xAccLeft = xAccLeft * 0.9f;
    }

    // Upwards acceleration constantly decreasing
    yAccUp = yAccUp * 0.9f;

    // Stop calculating speed if very small
    if (yAccUp <= 0.05){
        yAccUp = 0;
    }
    if (xAccRight <= 0.05){
        xAccRight = 0;
    }
    if (xAccLeft <= 0.05){
        xAccLeft = 0;
    }

    // Check for collisions
    checkCollisions();

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
