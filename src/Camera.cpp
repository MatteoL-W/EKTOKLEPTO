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
            if (speed < 0.1)
                speed = 0.15;
        } else {
            speed = 0;
        }
    } else {
        center = destination;
    }
}


void Camera::draw() {
    glViewport(-Engine::WINDOW_WIDTH * 0.5, -Engine::WINDOW_HEIGHT * (1 - playerYAxis), Engine::WINDOW_WIDTH * 2,
               Engine::WINDOW_HEIGHT * 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = Engine::WINDOW_WIDTH / (float) Engine::WINDOW_HEIGHT;

    // We are on an horizontal game
    gluOrtho2D(
            center.x + (-zoom / 2 * aspectRatio), center.x + (zoom / 2 * aspectRatio),
            center.y + (-zoom / 2), center.y + (zoom / 2)
    );

    glm::vec2 TLScreen = glm::vec2(
            1 + center.x + (-zoom / 2),
            center.y + (zoom / 2) * (1 - playerYAxis)
    );

    glm::vec2 BRScreen = glm::vec2(
            center.x + (zoom / 2) - 1,
            center.y + (-zoom / 2) * playerYAxis
    );

    map->getBoxes()->drawCorrespondingQuadForScreen(
            TLScreen,
            BRScreen
    );
}
