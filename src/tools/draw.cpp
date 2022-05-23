#include "../include/tools/draw.hpp"

void drawRect(glm::vec2 topLeftCoordinate, glm::vec2 bottomRightCoordinate, bool filled) {
    if (filled) {
        glBegin(GL_QUADS);
    } else {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2f(topLeftCoordinate.x, topLeftCoordinate.y);
    glVertex2f(bottomRightCoordinate.x, topLeftCoordinate.y);
    glVertex2f(bottomRightCoordinate.x, bottomRightCoordinate.y);
    glVertex2f(topLeftCoordinate.x, bottomRightCoordinate.y);
    glEnd();
}


void drawRect(glm::vec2 bottomLeftCoordinate, float width, float height, bool filled) {
    drawRect(
            glm::vec2(bottomLeftCoordinate.x, bottomLeftCoordinate.y + height),
            glm::vec2(bottomLeftCoordinate.x + width, bottomLeftCoordinate.y),
            filled
    );
}
