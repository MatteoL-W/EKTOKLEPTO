#include "GL/gl.h"
#include "../include/tools/utils.hpp"

/**
 * @brief Get the padding to align center a text according to the block
 * @param blockWidth
 * @param textWidth
 * @return
 */
int getPadding(int blockWidth, int textWidth) {
    return (blockWidth - textWidth) / 2;
}

/**
 * @brief Get the center of a square with topLeft / bottomRight coord
 * @param topLeftCoord
 * @param bottomRightCoord
 * @return
 */
glm::vec2 getPositionCenter(glm::vec2 topLeftCoord, glm::vec2 bottomRightCoord) {
    return {
            (bottomRightCoord.x - topLeftCoord.x) / 2 + topLeftCoord.x,
            (topLeftCoord.y - bottomRightCoord.y) / 2 + bottomRightCoord.y
    };
}

/**
 * @brief Get is a subject is between 2 limits
 * @param subject
 * @param limitA
 * @param limitB
 * @return
 */
bool isContained(float subject, float limitA, float limitB) {
    if (limitA > limitB) {
        return subject >= limitB && subject <= limitA;
    }
    return subject >= limitA && subject <= limitB;
}

void drawCurrentSquare(float x, float y) {
    glDisable(GL_BLEND);

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(x, y + 0.35, 0);
    glRotatef(45,0,0,1);

    glBegin(GL_QUADS);
    glVertex2f(0.25, 0.25);
    glVertex2f(-0.25, 0.25);
    glVertex2f(-0.25, -0.25);
    glVertex2f(0.25, -0.25);
    glEnd();
    glPopMatrix();
}
