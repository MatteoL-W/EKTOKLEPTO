#include "../include/Camera.hpp"
#include "../include/tools/Text.hpp"
#include "../include/variables/color.hpp"
#include <glm/gtx/norm.hpp>

/**
 * @brief Set the center of the camera according to the current player
 */

Text *levelText;

void Camera::update() {
    setZoom();

    glm::vec2 destination = map->getCurrentPlayer()->getCenteredPosition();

    if (center == destination) {
        unsetTrajectory();
    }

    if (center != destination) {
        setTrajectory(center, destination);

        if (distance > 0.1) {
            center = center + direction * speed;
            speed = (speed < 0.1) ? 0.15 : speed;
        } else {
            speed = 0;
        }
    }
}

void Camera::draw() {
    // Set viewport
    glViewport(-Engine::WINDOW_WIDTH * 0.5, -Engine::WINDOW_HEIGHT * (1 - playerYAxis), Engine::WINDOW_WIDTH * 2,
               Engine::WINDOW_HEIGHT * 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    centerOrthogonalSystem();
    drawLevelIndication();
}

void Camera::centerOrthogonalSystem() {
    gluOrtho2D(
            center.x + (-zoom * Engine::aspectRatio), center.x + (zoom * Engine::aspectRatio),
            center.y + (-zoom), center.y + (zoom)
    );
}

void Camera::setTrajectory(glm::vec2 initial, glm::vec2 final) {
    distance = glm::distance(initial, final);
    direction = glm::normalize(final - initial);
    speed = distance / (float) 10;
}

void Camera::unsetTrajectory() {
    distance = 0;
    direction = glm::vec2(0, 0);
    speed = 0;
}

/**
 * @brief Define new level text
 * @param level
 */
void Camera::newLevel(int level) {
    zoom = map->getMapZoom() * 8;
    levelText = new Text("LEVEL " + std::to_string(level), TTF_OpenFont("./assets/fonts/Press.ttf", 70), WhiteColor,
                         -0.28, 0.2);
}

/**
 * @brief Draw the new level indication with decreasing opacity
 */
void Camera::drawLevelIndication() {
    if (levelText) {
        glPushMatrix();
            glLoadIdentity();
            float opacity = (float)zoom / map->getMapZoom() / 8.;
            glColor4f(1, 1, 1, opacity);
            levelText->draw();
        glPopMatrix();
        glColor4f(1, 1, 1, 1);
    }
}

/**
 * @brief Update the zoom
 */
void Camera::setZoom() {
    if (zoom != map->getMapZoom()) {
        map->setDrawingStatus(true);
        zoom = zoom * 0.999;
        if (zoom < map->getMapZoom()) {
            zoom = map->getMapZoom();
            levelText = nullptr;
            map->setDrawingStatus(false);
        }
    } else {
        zoom = map->getMapZoom();
        levelText = nullptr;
        map->setDrawingStatus(false);
    }
}