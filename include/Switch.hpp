#pragma once

#include <vector>
#include "glm/vec2.hpp"
#include "Zone.hpp"

class Switch {
public:
    Switch(int p_id, int p_type, float p_x, float p_y):id(p_id), type(p_type), x(p_x), y(p_y) {};

    ~Switch() = default;

    void update();

    void draw();

    bool isActive() const { return active; };

    void setActivity(bool newState) { active = newState; };

    void linksToZones(std::vector<Zone*> zones);

    //std::vector<Zone*> getZones() { return zones; };

private:
    int id, type;

    float x, y;

    bool active = true;

    std::vector<Zone*> zonesLinked;
};
