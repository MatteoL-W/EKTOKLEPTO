#pragma once

#include <GL/glu.h>
#include "Engine.hpp"
#include "Map.hpp"

class Camera {
public:
    explicit Camera(Map *p_map)
    : map(p_map) {};

    ~Camera() = default;

    void update();

    void draw();

private:
    Map *map;

    glm::vec2 center;

    int zoom = 10;
};
