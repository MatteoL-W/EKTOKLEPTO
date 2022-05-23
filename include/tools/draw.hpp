#pragma once

#include <GL/gl.h>
#include "glm/vec2.hpp"

void drawRect(glm::vec2 topLeftCoordinate, glm::vec2 bottomRightCoordinate, bool filled = true);
void drawRect(glm::vec2 bottomLeftCoordinate, float width, float height, bool filled = true);