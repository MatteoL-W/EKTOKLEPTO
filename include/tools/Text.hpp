#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL_ttf.h"
#include <iostream>

class Text {
public:
    Text(std::string p_content, TTF_Font *p_font, SDL_Color p_color, float p_x, float p_y)
            : content(p_content), font(p_font), color(p_color), x(p_x), y(p_y) {
        apply();
    };

    ~Text() = default;

    void draw();

    void changeText(std::string newText) { content = std::move(newText);};

    void changeColor(SDL_Color newColor) { color = newColor;};

    void apply() { generateSurface(); bindTexture(); }

    void deleteTexture();

private:
    void generateSurface();

    void bindTexture();

    std::string content;

    TTF_Font *font;

    SDL_Color color;

    SDL_Surface* renderedText;

    GLuint textureBind = 0;

    float x, y;
};


