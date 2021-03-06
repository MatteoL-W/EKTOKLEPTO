#include <GL/gl.h>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/tools/draw.hpp"

void Player::draw() {
    if (!hasFinished && background) {
        glColor3f(1, 1, 1);
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

bool Player::isContained(float subject, float limitA, float limitB) {
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

        float boxLeft = nearBoxes[i]->getBLPosition().x + 0.001f;
        float boxRight = nearBoxes[i]->getBRPosition().x - 0.001f;
        float boxBottom = nearBoxes[i]->getBLPosition().y + 0.001f;
        float boxTop = nearBoxes[i]->getTLPosition().y - 0.001f;

        // if there is a collision detected (box bigger than player)
        if ( ( ( isContained(BLPosition.x, boxLeft, boxRight )
        || isContained(BLPosition.x + width, boxLeft, boxRight))
        && (isContained(BLPosition.y, boxBottom, boxTop)
        || isContained(BLPosition.y + height, boxBottom, boxTop) ) )
        // (player bigger than box)
        || ( ( isContained(nearBoxes[i]->getBLPosition().x, BLPosition.x, BLPosition.x + width)
        || isContained(nearBoxes[i]->getBRPosition().x, BLPosition.x, BLPosition.x + width))
        && (isContained(nearBoxes[i]->getBLPosition().y, BLPosition.y, BLPosition.y + height)
        || isContained(nearBoxes[i]->getTLPosition().y, BLPosition.y, BLPosition.y + height) ) ) )
        {
            hasTouchedGround = true;

            // player left / box right collision
            if (isContained(boxRight, savedBPx, BLPosition.x)
            || (isContained(BLPosition.x, boxRight + nearBoxes[i]->getHorizontalMovement() * 10, boxRight - nearBoxes[i]->getHorizontalMovement() * 10) && (nearBoxes[i]->isMovable()))){
                collisionLeft = true;
                BLPosition.x = boxRight;
                if (nearBoxes[i]->isMovable() && nearBoxes[i]->getHorizontalMovement() > 0){
                    BLPosition.x = boxRight + nearBoxes[i]->getHorizontalMovement() * 10;
                    xSpeedMod = nearBoxes[i]->getHorizontalMovement() * 10;
                    xAccRight += xAccLeft + 0.25f;
                }
                xAccLeft = 0.0;
            }

            // player right / box left collision
            if (isContained(boxLeft, savedBPx + width, BLPosition.x + width)
            || (isContained(BLPosition.x + width, boxLeft + nearBoxes[i]->getHorizontalMovement() * 10, boxLeft - nearBoxes[i]->getHorizontalMovement() * 10) && (nearBoxes[i]->isMovable()))){
                collisionRight = true;
                BLPosition.x = boxLeft - width;
                if (nearBoxes[i]->isMovable() && nearBoxes[i]->getHorizontalMovement() < 0){
                    BLPosition.x = boxLeft - width - nearBoxes[i]->getHorizontalMovement() * 10;
                    xSpeedMod = nearBoxes[i]->getHorizontalMovement() * 10;
                    xAccLeft += xAccRight + 0.25f;
                }
                xAccRight = 0.0;
            }

            // player bottom / box top collision (gravity) (can't happen at the same time as a lateral collision with the same box to prevent clipping on corners)
            if (( isContained(boxTop, savedBPy, BLPosition.y)
            || (isContained(BLPosition.y, boxTop + nearBoxes[i]->getHorizontalMovement() * 10, boxTop - nearBoxes[i]->getVerticalMovement() * 10) && (nearBoxes[i]->isMovable())))
            && ( (!isContained(boxLeft, savedBPx + width, BLPosition.x + width))
            && (!isContained(boxRight, savedBPx, BLPosition.x)) ) )
            {
                collisionBottom = true;
                BLPosition.y = boxTop;
                if (!warpedGravity){
                    if (toJump){
                        hasJumped = 1;
                    } else {
                        hasJumped = 0;
                    }
                    if (nearBoxes[i]->isMovable()){
                        xSpeedMod = nearBoxes[i]->getHorizontalMovement() * 10;
                    }
                    if (nearBoxes[i]->isMovable()  && nearBoxes[i]->getVerticalMovement() < 0){
                        BLPosition.y = boxTop + nearBoxes[i]->getVerticalMovement();
                    }
                    if (ySpeed < 0){
                        ySpeed = 0;
                    }
                } else {
                    if (ySpeed < 0){
                        gravityAcc -= 0.75;
                    }
                }
            }

            // player top / box bottom collision (can't happen at the same time as a lateral collision with the same box to prevent clipping on corners)
            if (isContained(boxBottom, savedBPy + height, BLPosition.y + height)
            && ( (!isContained(boxLeft, savedBPx + width, BLPosition.x + width))
            && (!isContained(boxRight, savedBPx, BLPosition.x)) ))
            {
                collisionTop = true;
                if (warpedGravity){
                    if (toJump){
                        hasJumped = 1;
                    } else {
                        hasJumped = 0;
                    }
                    if (ySpeed > 0){
                        ySpeed = 0;
                    }
                } else {
                    if (ySpeed > 0){
                        yAccUp -= 0.25;
                    }
                }
                noJumpCounter = 15;
                BLPosition.y = boxBottom - height;
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
            if (isContained(otherPlayers[j]->getBRPosition().x, savedBPx, BLPosition.x)) {
                collisionLeft = true;
                BLPosition.x = otherPlayers[j]->getBRPosition().x;
                xAccLeft = 0.0;
            }

            // current player right / other player left collision
            if (isContained(otherPlayers[j]->getBLPosition().x, savedBPx + width, BLPosition.x + width)) {
                collisionRight = true;
                BLPosition.x = otherPlayers[j]->getBLPosition().x - width;
                xAccRight = 0.0;
            }

            // current player bottom / other player top collision (gravity) (can't happen at the same time as a lateral collision with the same box to prevent clipping on corners)
            if (isContained(otherPlayers[j]->getTLPosition().y, savedBPy, BLPosition.y)
                && ((!isContained(otherPlayers[j]->getBLPosition().x, savedBPx + width, BLPosition.x + width))
                    && (!isContained(otherPlayers[j]->getBRPosition().x, savedBPx, BLPosition.x)))) {
                collisionBottom = true;
                if (!warpedGravity){
                    if (toJump){
                        hasJumped = 1;
                    } else {
                        hasJumped = 0;
                    }
                    if (ySpeed < 0){
                        ySpeed = 0;
                    }
                }
                if (BLPosition.y <= otherPlayers[j]->getTLPosition().y){
                    BLPosition.y = otherPlayers[j]->getTLPosition().y;
                }
            }

            // current player top / other player box bottom collision
            if (isContained(otherPlayers[j]->getBLPosition().y, savedBPy + height, BLPosition.y + height)
                && ( (!isContained(otherPlayers[j]->getBLPosition().x, savedBPx + width, BLPosition.x + width))
                     && (!isContained(otherPlayers[j]->getBRPosition().x, savedBPx, BLPosition.x)) )){
                collisionTop = true;
                if (warpedGravity){
                    if (toJump){
                        hasJumped = 1;
                    } else {
                        hasJumped = 0;
                    }
                    if (ySpeed > 0){
                        ySpeed = 0;
                    }
                } else {
                    if (ySpeed > 0){
                        ySpeed = 0;
                    }
                }
                if (BLPosition.y >= otherPlayers[j]->getBLPosition().y - height){
                    BLPosition.y = otherPlayers[j]->getBLPosition().y - height;
                }
            }
        }

        j++;
    }
}

void Player::jump() {
    toJump = true;
}

void Player::posUpdate() {
    if (hasFinished)
        return;

    // Reset speed modifiers (can be altered by moving boxes)
    xSpeedMod = 0.0;
    ySpeedMod = 0.0;

    // If arrow is pushed, max speed in that direction, else, speed is decreasing
    if (movingRight && !collisionRight && hasTouchedGround){
        xAccRight = 1.00;
    } else {
        xAccRight = xAccRight * 0.9f;
    }

    if (movingLeft && !collisionLeft && hasTouchedGround){
        xAccLeft = 1.00;
    } else {
        xAccLeft = xAccLeft * 0.9f;
    }


    // Upwards acceleration increases or decreases according to gravity direction
    if (!warpedGravity){
        yAccUp = yAccUp * 0.9f;
        if (gravityAcc < 1) {
            if (gravityAcc <= 0){
                gravityAcc = 0.05;
            }
            gravityAcc = gravityAcc * 1.1f;
        } else {
            gravityAcc = 1.0;
        }

    } else {
        gravityAcc = gravityAcc * 0.9f;
        if (yAccUp < 0.27) {
            if (yAccUp <= 0){
                yAccUp = 0.05;
            }
            yAccUp = yAccUp * 1.1f;
        } else {
            yAccUp = 0.27;
        }

    }

    // Check if jump was scheduled
    if (toJump && noJumpCounter == 0){
        if (hasJumped < 2){
            jumpSound->play();
            if (warpedGravity){
                gravityAcc = 3.6;
            } else if (superJump) {
                yAccUp = 5;
            } else {
                yAccUp = 1.00;
            }
            if (!collisionBottom){
                // walljump to right
                if (collisionLeft && !collisionRight){
                    xAccLeft = 0.0;
                    yAccUp = 1.20;
                    xAccRight = 1.50;
                }
                // walljump to left
                if (collisionRight && !collisionLeft){
                    xAccRight = 0.0;
                    xAccLeft = 1.50;
                    yAccUp = 1.20;
                }
            }
            hasJumped += 1;
        }
    }

    // Stop calculating speed if very small
    if (yAccUp <= 0.05){ yAccUp = 0; }
    if (gravityAcc <= 0.05){ gravityAcc = 0; }
    if (xAccRight <= 0.05){ xAccRight = 0; }
    if (xAccLeft <= 0.05){ xAccLeft = 0; }


    // Updating speed according to acceleration
    xSpeed = xMaxSpeed * xAccRight - xMaxSpeed * xAccLeft;
    ySpeed = yMaxSpeedUp * yAccUp - gravity * gravityAcc;


    // Check for collisions
    checkCollisions();

    // Account for collisions with moving blocks
    xSpeed += xSpeedMod;
    ySpeed += ySpeedMod;

    // Save current position for use in collision check during next frame
    savedBPy = BLPosition.y;
    savedBPx = BLPosition.x;

    // Update position
    BLPosition.x = BLPosition.x + xSpeed;
    BLPosition.y = BLPosition.y + ySpeed;

    // Jumping request has been processed
    toJump = false;
    if (noJumpCounter > 0){
        noJumpCounter -= 1;
    }
}

void Player::setInactive() {
    movingRight = false;
    movingLeft = false;
}

void Player::setPropsFromType() {
    enum Players {
        Joconde = 1, Marylin, Cri
    };

    switch (type) {
        case Joconde:
            width = 1;
            height = 1;
            r = 0.74;
            g = 0.3;
            b = 0.25;
            background = new Image("./assets/img/players/tab-50-50.png");
            ghost = new Image("./assets/img/players/tab-50-50-possessed.png");
            break;

        case Marylin:
            width = 0.5;
            height = 0.5;
            r = 0;
            g = 1;
            b = 0;
            background = new Image("./assets/img/players/tab-25-25.png");
            ghost = new Image("./assets/img/players/tab-25-25-possessed.png");
            break;

        case Cri:
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
    currentChanges = 2;
    width = (width <= fixWidth * 0.5) ? fixWidth * 0.5f : width * 0.92f;
    height = (height <= fixHeight * 0.5) ? fixHeight * 0.5f : height * 0.92f;
}

void Player::setMaxiMode() {
    currentChanges = 3;
    width = (width >= fixWidth * 3) ? fixWidth * 3 : width * 1.08f;
    height = (height >= fixHeight * 3) ? fixHeight * 3 : height * 1.08f;
}

void Player::unsetMiniMode() {
    width = (width < fixWidth) ? width * 1.08f : fixWidth;
    height = (height < fixHeight) ? height * 1.08f : fixHeight;
    if (width == fixWidth && height == fixHeight) { currentChanges = -1; }
}

void Player::unsetMaxiMode() {
    width = (width > fixWidth) ? width * 0.92f : fixWidth;
    height = (height > fixHeight) ? height * 0.92f : fixHeight;
    if (width == fixWidth && height == fixHeight) { currentChanges = -1; }
}

void Player::setWarpedGravity() {
    warpedGravity = true;
}

void Player::unsetWarpedGravity() {
    warpedGravity = false;
}

void Player::drawGhost() {
    glColor3f(1,1,1);
    ghost->draw(BLPosition, width, height);
}

void Player::removeCurrentFromArray(size_t id) {
    otherPlayers.erase(otherPlayers.begin() + (int) id);
}
