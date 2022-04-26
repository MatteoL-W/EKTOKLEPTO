#include <GL/gl.h>
#include "../include/Box.hpp"
#include "../include/tools/draw.hpp"

Box::~Box() {}

void Box::draw() {
    glColor3f(1, 1, 1);
    drawRect(TLPosition, BRPosition);
}
