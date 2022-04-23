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
    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();
}

