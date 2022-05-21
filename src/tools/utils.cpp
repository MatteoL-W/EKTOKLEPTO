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
