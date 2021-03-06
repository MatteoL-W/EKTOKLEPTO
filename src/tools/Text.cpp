#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Engine.hpp"
#include "../../include/tools/Text.hpp"

void Text::generateSurface() {
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderedText = TTF_RenderText_Blended(const_cast<TTF_Font *>(font), content.c_str(), color);
}

void Text::bindTexture() {
    glGenTextures(1, &textureBind);
    glBindTexture(GL_TEXTURE_2D, textureBind);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Text::draw() {
    glEnable(GL_BLEND);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, renderedText->w, renderedText->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,renderedText->pixels);

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + ((float)renderedText->w), y);
        glTexCoord2d(1, 0); glVertex2f(x + ((float)renderedText->w), y + (float)renderedText->h);
        glTexCoord2d(0, 0); glVertex2f(x, y + (float)renderedText->h );
    glEnd();

    glDisable(GL_BLEND);
}

void Text::drawInGame() {
    glEnable(GL_BLEND);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, renderedText->w, renderedText->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,renderedText->pixels);

    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex2f(x, y);
    glTexCoord2d(1, 1); glVertex2f(x + ((float)renderedText->w / (Engine::WINDOW_WIDTH)) * Engine::aspectRatio, y);
    glTexCoord2d(1, 0); glVertex2f(x + ((float)renderedText->w / (Engine::WINDOW_WIDTH)) * Engine::aspectRatio, y + (float)renderedText->h / (Engine::WINDOW_HEIGHT));
    glTexCoord2d(0, 0); glVertex2f(x, y + (float)renderedText->h / (Engine::WINDOW_HEIGHT));
    glEnd();

    glDisable(GL_BLEND);
}

void Text::deleteTexture() {
    glDeleteTextures(1, &textureBind);
    SDL_FreeSurface(renderedText);
}
