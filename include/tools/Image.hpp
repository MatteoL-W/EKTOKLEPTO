#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <utility>

class Image {
public:
    Image(std::string p_path, float p_x, float p_y, float p_divider)
            : path(std::move(p_path)), x(p_x), y(p_y), divider(p_divider) {
        apply();
    };

    ~Image() = default;

    void draw();

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


