#include <GL/gl.h>
#include "../include/Box.hpp"

Box::Box(int p_xCoord1, int p_yCoord1, int p_xCoord2, int p_yCoord2) {
    xCoord1 = p_xCoord1;
    yCoord1 = p_yCoord1;
    xCoord2 = p_xCoord2;
    yCoord2 = p_yCoord2;
}

Box::~Box() {}

void Box::draw() {
    glBegin(GL_QUADS);
    glColor3f(1., 0, 0);
    glVertex2f(xCoord1, yCoord1);
    glVertex2f(xCoord2, yCoord1);
    glVertex2f(xCoord2, yCoord2);
    glVertex2f(xCoord1, yCoord2);
    glEnd();
}