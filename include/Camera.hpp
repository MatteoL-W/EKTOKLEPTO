#pragma once

#include <GL/glu.h>
#include "Engine.hpp"
#include "Map.hpp"

class Camera {
public:
    Camera(Map *p_map, int p_zoom)
            : map(p_map), center(map->getPlayers()[0]->getCenteredPosition()), zoom(p_zoom) {};

    ~Camera() = default;

    void update();

    void draw();

    void setTrajectory(glm::vec2 initial, glm::vec2 final);

    void setMap(Map *newMap) { map = newMap; };

    void newLevel(int level);

    void setZoom(int newZoom) { zoom = newZoom; };

    void unsetTrajectory();


private:

    void centerOrthogonalSystem();

    void drawLevelIndication();

    void setZoom();

    Map *map;

    glm::vec2 center;

    glm::vec2 direction;
    float speed;
    float distance;

    int zoom;
    float playerYAxis = Engine::PLAYER_Y_AXIS;
};
