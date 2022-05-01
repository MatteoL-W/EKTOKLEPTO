#pragma once

#include <GL/glu.h>
#include "Engine.hpp"
#include "Map.hpp"

class Camera {
public:
    explicit Camera(Map *p_map, int p_zoom)
            : map(p_map), center(map->getPlayers()[0]->getCenteredPosition()), zoom(p_zoom) {};

    ~Camera() = default;

    void update();

    void draw();

    void setTrajectory(glm::vec2 initial, glm::vec2 final);

private:
    void drawCameraContent();

    void centerOrthogonalSystem();

    Map *map;

    glm::vec2 center;

    glm::vec2 direction;
    float speed;
    float distance;

    int zoom;
    float playerYAxis = 0.25;
};
