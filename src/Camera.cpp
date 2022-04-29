#include "../include/Camera.hpp"
#include <glm/gtx/norm.hpp>

void Camera::update() {
    glm::vec2 destination = map->getCurrentPlayer()->getCenteredPosition();
    direction = glm::normalize(destination - center);
    distance = glm::distance(center, destination);

    if (center != destination) {
        if (speed == 0) {
            center = destination;
            return;
        }

        if (distance > 0.1) {
            center = center + direction * speed;
            speed *= 0.9;
            if (speed < 0.01)
                speed = 0.05;
        } else {
            speed = 0;
        }
    }

    else {
        center = direction;
    }
}


void Camera::draw() {
    glViewport(-Engine::WINDOW_WIDTH / 2, -Engine::WINDOW_HEIGHT / 1.4, Engine::WINDOW_WIDTH * 2,
               Engine::WINDOW_HEIGHT * 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = Engine::WINDOW_WIDTH / (float) Engine::WINDOW_HEIGHT;

    if (aspectRatio > 1) {
        gluOrtho2D(
                center.x + (-zoom * aspectRatio), center.x + (zoom * aspectRatio),
                center.y + (-zoom), center.y + (zoom));
    } else {
        gluOrtho2D(
                center.x + (-zoom), center.x + (zoom / 2.),
                center.y + (-zoom / aspectRatio), center.y + (zoom / aspectRatio));
    }
}
