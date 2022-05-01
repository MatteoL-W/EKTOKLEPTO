#include "../include/Camera.hpp"
#include <glm/gtx/norm.hpp>

/**
 * @brief Set the center of the camera according to the current player
 */
void Camera::update() {
    glm::vec2 destination = map->getCurrentPlayer()->getCenteredPosition();
    setTrajectory(center, destination);

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
        unsetTrajectory();
    }
}

void Camera::draw() {
    // Set viewport
    glViewport(-Engine::WINDOW_WIDTH * 0.5, -Engine::WINDOW_HEIGHT * (1 - playerYAxis), Engine::WINDOW_WIDTH * 2,
               Engine::WINDOW_HEIGHT * 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    centerOrthogonalSystem();
    drawCameraContent();
}

void Camera::centerOrthogonalSystem() {
    float aspectRatio = Engine::WINDOW_WIDTH / (float) Engine::WINDOW_HEIGHT;

    gluOrtho2D(
            center.x + (-zoom * aspectRatio), center.x + (zoom * aspectRatio),
            center.y + (-zoom), center.y + (zoom)
    );
}

void Camera::drawCameraContent() {
    glm::vec2 TLScreen = glm::vec2(
            1 + center.x + (-zoom),
            center.y + (zoom) * (1 - playerYAxis)
    );

    glm::vec2 BRScreen = glm::vec2(
            center.x + (zoom) - 1,
            center.y + (-zoom) * playerYAxis
    );

    map->getBoxes()->drawCorrespondingQuadForScreen(
            TLScreen,
            BRScreen
    );
}

void Camera::setTrajectory(glm::vec2 initial, glm::vec2 final) {
    distance = glm::distance(initial, final);
    direction = glm::normalize(final - initial);
    speed = distance / (float)10;
}

void Camera::unsetTrajectory() {
    distance = 0;
    direction = glm::vec2(0,0);
    speed = 0;
}