#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../include/Engine.hpp"
#include "../../include/tools/Image.hpp"

void Image::generateSurface() {
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    imageSurface = IMG_Load(path.c_str());
}

void Image::bindTexture() {
    glGenTextures(1, &textureBind);
    glBindTexture(GL_TEXTURE_2D, textureBind);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Image::draw() {
    glEnable(GL_BLEND);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,imageSurface->pixels);

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + (float)imageSurface->w/divider, y);
        glTexCoord2d(1, 0); glVertex2f(x + (float)imageSurface->w/divider, y + (float)imageSurface->h/divider);
        glTexCoord2d(0, 0); glVertex2f(x, y + (float)imageSurface->h/divider);
    glEnd();

    glDisable(GL_BLEND);
}

void Image::draw(glm::vec2 BL, float width, float height) {
    glEnable(GL_BLEND);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,imageSurface->pixels);

    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex2f(BL.x, BL.y);
    glTexCoord2d(1, 1); glVertex2f(BL.x + width, BL.y);
    glTexCoord2d(1, 0); glVertex2f(BL.x + width, BL.y + height);
    glTexCoord2d(0, 0); glVertex2f(BL.x, BL.y + height);
    glEnd();

    glDisable(GL_BLEND);
}

void Image::deleteTexture() {
    glDeleteTextures(1, &textureBind);
    SDL_FreeSurface(imageSurface);
}
