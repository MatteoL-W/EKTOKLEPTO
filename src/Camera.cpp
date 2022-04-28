#include "../include/Camera.hpp"

void Camera::update() {
    center = map->getCurrentPlayer()->getCenteredPosition();
}

void Camera::draw() {
    glViewport(0, 0, Engine::WINDOW_WIDTH, Engine::WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = Engine::WINDOW_WIDTH / (float) Engine::WINDOW_HEIGHT;

    if (aspectRatio > 1) {
        gluOrtho2D(
                center.x + (-zoom / 2. * aspectRatio), center.x + (zoom / 2. * aspectRatio),
                center.y + (-zoom / 2.), center.y + (zoom / 2.));
    } else {
        gluOrtho2D(
                center.x + (-zoom / 2.), center.x + (zoom / 2.),
                center.y + (-zoom / 2. / aspectRatio), center.y + (zoom / 2. / aspectRatio));
    }
}
