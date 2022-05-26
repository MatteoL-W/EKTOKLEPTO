#include <GL/gl.h>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

void Player::draw() {
    if (!hasFinished && background) {
        glColor3f(1,1,1);
        background->draw(BLPosition, width, height);
        return;
    }

    if (!hasFinished)
        glColor3f(r, g, b);
    else
        glColor3f(255, 255, 255);

    drawRect(BLPosition, width, height);
}

void Player::drawEndPlace() {
    glColor3f(r, g, b);
    drawRect(BLPositionEnd, fixWidth, fixHeight, false);
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

    // player/box collision
    size_t i = 0;
    while (i < nearBoxes.size()) {  // for each box close to the player

        // if there is a collision detected (box bigger than player)
        if ( ( ( isContained(BLPosition.x, nearBoxes[i]->getBLPosition().x, nearBoxes[i]->getBRPosition().x)
        || isContained(BLPosition.x + width, nearBoxes[i]->getBLPosition().x, nearBoxes[i]->getBRPosition().x))
        && (isContained(BLPosition.y, nearBoxes[i]->getBLPosition().y, nearBoxes[i]->getTLPosition().y)
        || isContained(BLPosition.y + height, nearBoxes[i]->getBLPosition().y, nearBoxes[i]->getTLPosition().y) ) )
        // (player bigger than box)
        || ( ( isContained(nearBoxes[i]->getBLPosition().x, BLPosition.x, BLPosition.x + width)
        || isContained(nearBoxes[i]->getBRPosition().x, BLPosition.x, BLPosition.x + width))
        && (isContained(nearBoxes[i]->getBLPosition().y, BLPosition.y, BLPosition.y + height)
        || isContained(nearBoxes[i]->getTLPosition().y, BLPosition.y, BLPosition.y + height) ) ) )
        {

            // player left / box right collision
            if (isContained(nearBoxes[i]->getBRPosition().x, savedBPx, BLPosition.x)){
                collisionLeft = true;
                BLPosition.x = nearBoxes[i]->getBRPosition().x;
                xAccLeft = 0.0;
            }

            // player right / box left collision
            if (isContained(nearBoxes[i]->getBLPosition().x, savedBPx + width, BLPosition.x + width)){
                collisionRight = true;
                BLPosition.x = nearBoxes[i]->getBLPosition().x - width;
                xAccRight = 0.0;
            }

            // player bottom / box top collision (gravity) (can't happen at the same time as a lateral collision with the same box to prevent clipping on corners)
            if ( isContained(nearBoxes[i]->getTLPosition().y, savedBPy, BLPosition.y)
            && ( (!isContained(nearBoxes[i]->getBLPosition().x, savedBPx + width, BLPosition.x + width))
            && (!isContained(nearBoxes[i]->getBRPosition().x, savedBPx, BLPosition.x)) ) )
            {
                collisionBottom = true;
                hasJumped = false;
                hasDoubleJumped = false;
                BLPosition.y = nearBoxes[i]->getTLPosition().y;
                if (ySpeed < 0){
                    ySpeed = 0;
                }
                if (nearBoxes[i]->isMovable()){
                    xSpeedMod += nearBoxes[i]->getSpeed();
                }
            }

            // player top / box bottom collision
            if (isContained(nearBoxes[i]->getBLPosition().y, savedBPy + height, BLPosition.y + height)){
                collisionTop = true;
                BLPosition.y = nearBoxes[i]->getBLPosition().y - height;
                if (ySpeed > 0){
                    yAccUp -= 0.25;
                }
            }
        }

        i++;
    }

    //  player/player collision
    size_t j = 0;
    while (j < otherPlayers.size()) {

        // if there is a collision detected (other player bigger than current player)
        if ( ( ( ( isContained(BLPosition.x, otherPlayers[j]->getBLPosition().x, otherPlayers[j]->getBRPosition().x)
        || isContained(BLPosition.x + width, otherPlayers[j]->getBLPosition().x, otherPlayers[j]->getBRPosition().x))
        && (isContained(BLPosition.y, otherPlayers[j]->getBLPosition().y, otherPlayers[j]->getTLPosition().y)
        || isContained(BLPosition.y + height, otherPlayers[j]->getBLPosition().y, otherPlayers[j]->getTLPosition().y) ) )
        // (player bigger than box)
        || ( ( isContained(otherPlayers[j]->getBLPosition().x, BLPosition.x, BLPosition.x + width)
        || isContained(otherPlayers[j]->getBRPosition().x, BLPosition.x, BLPosition.x + width))
        && (isContained(otherPlayers[j]->getBLPosition().y, BLPosition.y, BLPosition.y + height)
        || isContained(otherPlayers[j]->getTLPosition().y, BLPosition.y, BLPosition.y + height) ) ) )
        // and if the other player has not finished
        && !otherPlayers[j]->getStatus())
        {

            // current player left / other player right collision
            if (isContained(otherPlayers[j]->getBRPosition().x, savedBPx, BLPosition.x)){
                collisionLeft = true;
                BLPosition.x = otherPlayers[j]->getBRPosition().x;
                xAccLeft = 0.0;
            }

            // current player right / other player left collision
            if (isContained(otherPlayers[j]->getBLPosition().x, savedBPx + width, BLPosition.x + width)){
                collisionRight = true;
                BLPosition.x = otherPlayers[j]->getBLPosition().x - width;
                xAccRight = 0.0;
            }

            // current player bottom / other player top collision (gravity) (can't happen at the same time as a lateral collision with the same box to prevent clipping on corners)
            if ( isContained(otherPlayers[j]->getTLPosition().y, savedBPy, BLPosition.y)
            && ( (!isContained(otherPlayers[j]->getBLPosition().x, savedBPx + width, BLPosition.x + width))
            && (!isContained(otherPlayers[j]->getBRPosition().x, savedBPx, BLPosition.x)) ) )
            {
                collisionBottom = true;
                hasJumped = false;
                hasDoubleJumped = false;
                BLPosition.y = otherPlayers[j]->getTLPosition().y;
                if (ySpeed < 0){
                    ySpeed = 0;
                }
            }

            // current player top / other player box bottom collision
            if (isContained(otherPlayers[j]->getBLPosition().y, savedBPy + height, BLPosition.y + height)){
                collisionTop = true;
                BLPosition.y = otherPlayers[j]->getBLPosition().y - height;
                if (ySpeed > 0){
                    yAccUp -= 0.25;
                }
            }
        }

        j++;
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
    if (hasFinished)
        return;

    // Reset xSpeed modifier (can be altered by moving boxes)
    xSpeedMod = 0.0;

    // If arrow is pushed, max speed in that direction, else, speed is decreasing
    if (movingRight && !collisionRight){
        xAccRight = 1.00;
    } else {
        xAccRight = xAccRight * 0.9f;
    }

    if (movingLeft && !collisionLeft){
        xAccLeft = 1.00;
    } else {
        xAccLeft = xAccLeft * 0.9f;
    }

    // Upwards acceleration decreases constantly
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

    // Updating speed according to acceleration
    xSpeed = xMaxSpeed * xAccRight - xMaxSpeed * xAccLeft + xSpeedMod;
    ySpeed = yMaxSpeedUp * yAccUp - gravity;

    // Check for collisions
    checkCollisions();

    // Save current position for use in collision check during next frame
    savedBPy = BLPosition.y;
    savedBPx = BLPosition.x;

    // Update position
    BLPosition.x = BLPosition.x + xSpeed;
    BLPosition.y = BLPosition.y + ySpeed;

}

void Player::setPropsFromType() {
    enum Players {
        Orange = 1, Green
    };

    switch (type) {
        case Orange:
            width = 1;
            height = 1;
            r = 0.74;
            g = 0.3;
            b = 0.25;
            background = new Image("./assets/img/players/tab-50-50.png");
            ghost = new Image("./assets/img/players/tab-50-50-possessed.png");
            break;

        case Green:
            width = 0.5;
            height = 0.5;
            r = 0;
            g = 1;
            b = 0;
            background = new Image("./assets/img/players/tab-25-25.png");
            ghost = new Image("./assets/img/players/tab-25-25-possessed.png");
            break;
        case 3:
            width = 1;
            height = 2;
            r = 1;
            g = 0.5;
            b = 0.2;
            background = new Image("./assets/img/players/tab-100-50.png");
            ghost = new Image("./assets/img/players/tab-100-50-possessed.png");
            break;
    }

    fixWidth = width;
    fixHeight = height;
}

void Player::setMiniMode() {
    width = (width <= fixWidth * 0.5) ? fixWidth * 0.5f : width * 0.92;
    height = (height <= fixHeight * 0.5) ? fixHeight * 0.5f : height * 0.92;
}

void Player::unsetMiniMode() {
    width = (width < fixWidth) ? width * 1.08 : fixWidth;
    height = (height < fixHeight) ? height * 1.08 : fixHeight;
}

void Player::drawGhost() {
    glColor3f(1,1,1);
    ghost->draw(BLPosition, width, height);
}

void Player::removeCurrentFromArray(size_t id) {
    otherPlayers.erase(otherPlayers.begin() + (int)id);
}
