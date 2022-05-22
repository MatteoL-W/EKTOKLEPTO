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

    void drawZones();

    bool isActive() const { return active; };

    void setActivity(bool newState) { active = newState; };

    void linksToZones(std::vector<Zone*> &zones);

    std::vector<Zone*> getZones() { return zonesLinked; };

    void activate();
    void deactivate();

    float getX() const { return x; };
    float getY() const { return y; };

private:
    int id, type;

    float x, y, top = 0.2;

    bool active = false;

    std::vector<Zone*> zonesLinked;
};
