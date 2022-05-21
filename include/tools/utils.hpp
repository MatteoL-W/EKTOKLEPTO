#pragma once

#include "glm/vec2.hpp"

int getPadding(int blockWidth, int textWidth);

glm::vec2 getPositionCenter(glm::vec2 topLeftCoord, glm::vec2 bottomRightCoord);

bool isContained(float subject, float limitA, float limitB);

void drawCurrentSquare(float x, float y);