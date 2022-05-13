#include "../include/Switch.hpp"
#include "../include/tools/draw.hpp"
#include <iostream>

void Switch::draw() {
    drawRect(glm::vec2(x - 0.2, y + 0.2), glm::vec2(x + 0.2, y));
}

void Switch::linksToZones(std::vector<Zone *> zones) {
    for (size_t i = 0; i < zones.size(); i++) {
        if (zones[i]->getIdSwitch() == id) {
            zonesLinked.push_back(zones[i]);
        }
        zones.erase(zones.begin() + i);

    }

}
