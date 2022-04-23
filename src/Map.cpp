#include <fstream>
#include <GL/gl.h>
#include "../include/Map.hpp"

Map::Map() {

}

/**
 * @brief Update the map
 */
void Map::update() {

}

/**
 * @brief Draw the map
 */
void Map::draw() {
    glBegin(GL_QUADS);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 9.0 , 0.0);
    glVertex2f( 9.0 , -1.0);
    glVertex2f( 0.0 , -1.0);

    glEnd();
}

