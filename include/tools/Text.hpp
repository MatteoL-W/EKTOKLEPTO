#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL_ttf.h"
#include <iostream>

class Text {
public:
    Text() {}

    ~Text() = default;

    void create(std::string text, SDL_Color color, std::string fontName);

    void draw();

    void changeText(std::string newText);

    void changeColor(SDL_Color newColor);

    void changeDestRect(int x, int y);

    void changeFont(std::string name, int size);

    int getSize() { return size; };

    SDL_Rect getDestRect() { return destRect; };

    std::string getText() { return message; };

private:
    void createOpenGL(const std::string& text, const SDL_Color color, const std::string& fontName);

    std::string message;

    TTF_Font *font;

    SDL_Surface *surface;

    SDL_Color color;

    SDL_Texture *texture;

    SDL_Rect destRect;

    int size = 24;
};

TTF_Font *createFont(Text *text, std::string fontName);

SDL_Rect createDestRect(TTF_Font *font, std::string text, int x, int y);

void RenderText(const TTF_Font *Font, const GLubyte &R, const GLubyte &G, const GLubyte &B, const GLubyte &A,
                const double &X, const double &Y, const std::string &Text);


