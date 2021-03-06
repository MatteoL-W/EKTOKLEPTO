#include "../include/Zone.hpp"
#include "../include/tools/draw.hpp"

void Zone::initValues() {
    switch (idChange) {
        case ReverseGravity:
            r = 0;
            g = 0;
            b = 1;
            break;
        case Mini:
            r = 1;
            g = 0.15;
            b = 0;
            break;
        case Maxi:
            r = 0.7;
            g = 0;
            b = 0.2;
            break;
        case Jump:
            r = 0;
            g = 0.6;
            b = 0;
            break;
    }
}

void Zone::draw() {
    glColor3f(r, g, b);
    drawRect(TL, BR, true);
}

bool Zone::contains(glm::vec2 playerBL, glm::vec2 playerBR) {
    if ((TL.x <= playerBL.x && playerBL.x <= BR.x) && (BR.y <= playerBL.y && playerBL.y <= TL.y)
        && (TL.x <= playerBR.x && playerBR.x <= BR.x) && (BR.y <= playerBR.y && playerBR.y <= TL.y)) {
        return true;
    }
    return false;
}

void Zone::applyChanges(Player *currentPlayer) {
    switch (idChange) {
        case ReverseGravity:
            currentPlayer->setWarpedGravity();
            break;
        case Mini:
            currentPlayer->setMiniMode();
            break;
        case Maxi:
            currentPlayer->setMaxiMode();
            break;
        case Jump:
            currentPlayer->setSuperJumpMode();
            break;
    }
}
