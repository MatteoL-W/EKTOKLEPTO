#include <GL/gl.h>
#include "../include/Box.hpp"
#include "../include/tools/draw.hpp"

Box::~Box() {}

void Box::draw() {
    glColor3f(0, 0, 0);
    drawRect(TLPosition, BRPosition);
}
