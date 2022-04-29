#pragma once

#include <GL/glu.h>
#include "Engine.hpp"
#include "Map.hpp"

class Camera {
public:
    explicit Camera(Map *p_map, int p_zoom)
    : map(p_map), center(map->getPlayers()[0]->getCenteredPosition()), zoom(p_zoom){};

    ~Camera() = default;

    void update();

    void draw();

    void setSpeed(float p_speed) { speed = p_speed; };

    void setDirection(glm::vec2 p_direction) { direction = p_direction; };

    void setDistance(float p_distance) { distance = p_distance; };

private:
    Map *map;

    glm::vec2 center;

    glm::vec2 direction;
    float speed;
    float distance;
    float friction = 0.5;

    int zoom;
};
