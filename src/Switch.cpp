#include "../include/Switch.hpp"
#include "../include/tools/draw.hpp"

void Switch::insertZone(glm::vec2 TL, glm::vec2 BR) {
    Zone* newZone = new Zone(TL, BR);
    zones.push_back(newZone);
}

void Switch::draw() {
    drawRect(glm::vec2(x - 0.2, y + 0.2), glm::vec2(x + 0.2, y));

    for (size_t i = 0; i < zones.size(); i++)
        zones[i]->draw();
}
