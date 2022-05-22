#include <GL/gl.h>
#include "../include/Box.hpp"
#include "../include/tools/draw.hpp"

Box::~Box() {}

void Box::draw() {
    glColor3f(0, 0, 0);
    drawRect(TLPosition, BRPosition);
}

void Box::update() {
    if (glm::distance(TLPosition, TLDestination) < 0.01)
        TLPosition = TLDestination;

    if (TLDestination == TLPosition) {
        TLDestination = (TLDestination == TLInitialPosition) ? TLMaxPosition : TLInitialPosition;
        direction = glm::normalize(TLDestination - TLPosition);
    }

    TLPosition = TLPosition + direction * speed;
    BRPosition = BRPosition + direction * speed;
}

