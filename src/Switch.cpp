#include "../include/Switch.hpp"
#include "../include/tools/draw.hpp"


void Switch::draw() {
    drawRect(glm::vec2(x - 0.2, y + 0.2), glm::vec2(x + 0.2, y));
}
