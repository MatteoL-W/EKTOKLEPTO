#include <GL/gl.h>

void drawRect(int x1, int y1, int x2, int y2, bool filled = true) {
    if (filled) {
        glBegin(GL_QUADS);
    } else {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}
