#include <algorithm>
#include "../include/Switch.hpp"
#include "../include/tools/draw.hpp"


void Switch::update() {
    // get if the switch is active
}

void Switch::draw() {
    glColor3f(1,1,1);
    drawRect(glm::vec2(x - 0.2, y + top), glm::vec2(x + 0.2, y));
}

void Switch::linksToZones(std::vector<Zone *> &zones) {
    for (size_t i = 0; i < zones.size(); i++) {
        if (zones[i]->getIdSwitch() == id) {
            zonesLinked.push_back(zones[i]);
        }
    }

    zones.erase(
            std::remove_if(
                    zones.begin(),
                    zones.end(),
                    [this](Zone *const &current) { return current->getIdSwitch() == id; }
            ),
            zones.end()
    );
}

void Switch::drawZones() {
    if (isActive()) {
        for (auto zone: zonesLinked) {
            zone->draw();
        }
    }
}

void Switch::activate() {
    top *= 0.5;
    active = true;
}

void Switch::deactivate() {
    top = 0.2;
    active = false;
}
