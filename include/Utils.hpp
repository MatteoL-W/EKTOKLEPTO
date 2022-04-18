#pragma once

/**
 * @brief Get the padding to align center a text according to the block
 * @param blockWidth
 * @param textWidth
 * @return
 */
int getPadding(int blockWidth, int textWidth) {
    return (blockWidth - textWidth) / 2;
}