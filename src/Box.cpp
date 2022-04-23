#include <GL/gl.h>
#include "../include/Box.hpp"
#include "../include/tools/draw.hpp"

Box::~Box() {}

void Box::draw() {
    glColor3f(1., 0, 0);
    drawRect(xCoord1, yCoord1, xCoord2, yCoord2);
}