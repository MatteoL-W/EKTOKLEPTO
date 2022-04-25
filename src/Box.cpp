#include <GL/gl.h>
#include "../include/Box.hpp"
#include "../include/tools/draw.hpp"

Box::~Box() {}

void Box::draw() {
    glColor3f(0, 0, 0);
    drawRect(TLPosition, BRPosition);
    //glColor3f(1, 0, 0);
    //drawRect(glm::vec2(getPositionCenter().x-0.2, getPositionCenter().y+0.2),glm::vec2(getPositionCenter().x+0.2, getPositionCenter().y-0.2));
}
