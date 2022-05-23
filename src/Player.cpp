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

    drawRect(
            glm::vec2(BLPosition.x, BLPosition.y + height),
            glm::vec2(BLPosition.x + width, BLPosition.y)
    );
}


void Player::drawEndPlace() {
    //glColor3f(r, g, b);
    drawRect(
            glm::vec2(BLPositionEnd.x, BLPositionEnd.y + fixHeight),
            glm::vec2(BLPositionEnd.x + fixWidth, BLPositionEnd.y),
            false
    );
}

void Player::moveRight() {
    BLPosition.x += 0.01;
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
            background = new Image("./assets/img/player1_bg.png");
            break;

        case Green:
            width = 0.5;
            height = 0.5;
            r = 0;
            g = 1;
            b = 0;
            background = new Image("./assets/img/player1_bgtest.png");
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
    ghost->draw(BLPosition, width, height);
}
