#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <utility>

class Image {
public:
    Image(std::string p_path, float p_x = 0, float p_y = 0, float p_divider = 0)
            : path(std::move(p_path)), x(p_x), y(p_y), divider(p_divider) {
        apply();
    };

    ~Image() = default;

    void draw();
    void draw(glm::vec2 BL, float width, float height);

    void apply() { generateSurface(); bindTexture(); }

    void deleteTexture();

private:
    void generateSurface();

    void bindTexture();

    std::string path;

    SDL_Surface* imageSurface;

    GLuint textureBind = 0;

    float x, y, divider;
};


