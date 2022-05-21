#include "../include/Minimap.hpp"

void Minimap::draw() {
    glPushMatrix();
        //glLoadIdentity();
        //glMatrixMode(GL_PROJECTION);

        //gluViewpoort
        gluOrtho2D(0, map->getMapWidth(), 0, map->getMapHeight());
        glColor3f(0, 0, 0);

        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(2, 0);
            glVertex2f(2, 2);
            glVertex2f(0, 2);
        glEnd();
    glPopMatrix();
}

void Minimap::update() {}