#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../include/Engine.hpp"
#include "../include/tools/Text.hpp"

/**
 * @brief Create a text
 * @param text
 * @param color
 * @param fontName
 */
void Text::create(const std::string text, const SDL_Color color, const std::string fontName) {
    Text::message = text;
    Text::color = color;
    Text::font = createFont(this, fontName);
    Text::surface = TTF_RenderText_Solid(Text::font, Text::message.c_str(), Text::color);
    Text::texture = SDL_CreateTextureFromSurface(Engine::renderer, Text::surface);
    Text::destRect = createDestRect(Text::font, Text::message, 0, 0);
}

/**
 * @brief Draw the text
 */
void Text::draw() {
    SDL_RenderCopy(Engine::renderer, Text::texture, NULL, &(Text::destRect));
}

/**
 * @brief Change the text
 * @param newText
 */
void Text::changeText(const std::string newText) {
    SDL_FreeSurface(Text::surface);
    SDL_DestroyTexture(Text::texture);
    Text::message = newText.c_str();
    Text::surface = TTF_RenderText_Solid(Text::font, Text::message.c_str(), Text::color);
    Text::texture = SDL_CreateTextureFromSurface(Engine::renderer, Text::surface);
    Text::destRect = createDestRect(Text::font, Text::message, 0, 0);
}

/**
 * @brief Change the color
 * @param newText
 */
void Text::changeColor(const SDL_Color newColor) {
    SDL_FreeSurface(Text::surface);
    SDL_DestroyTexture(Text::texture);
    Text::color = newColor;
    Text::surface = TTF_RenderText_Solid(Text::font, Text::message.c_str(), Text::color);
    Text::texture = SDL_CreateTextureFromSurface(Engine::renderer, Text::surface);
    Text::destRect = createDestRect(Text::font, Text::message, 0, 0);
}

/**
 * @brief Change the x and y position
 * @param x
 * @param y
 */
void Text::changeDestRect(const int x, const int y) {
    Text::destRect = createDestRect(Text::font, Text::message, x, y);
}

/**
 * @brief Change the font (and its size)
 * @param size
 */
void Text::changeFont(const std::string name, const int size) {
    TTF_CloseFont(Text::font);
    Text::size = size;
    Text::font = createFont(this, name);
}

/**
 * @brief Returns a TTF_Font* from a simple string if the font is located in assets.
 * @param fontName
 * @return TTF_Font*
 */
TTF_Font *createFont(Text *text, const std::string fontName) {
    std::string fullFontName = "./assets/fonts/" + fontName + ".ttf";
    TTF_Font *font = TTF_OpenFont(fullFontName.c_str(), text->getSize());

    if (font == nullptr) {
        std::cout << fullFontName << " -> " << "Font not found" << std::endl;
    }

    return font;
}

/**
 * @brief Create a SDL_Rect by using the TTF_SizeText to calculate the right width/height of the font
 * @param font
 * @param text
 * @return SDL_Rect
 */
SDL_Rect createDestRect(TTF_Font *font, const std::string text, const int x, const int y) {
    SDL_Rect destMessage;
    destMessage.x = x;
    destMessage.y = y;

    if (TTF_SizeText(font, text.c_str(), &destMessage.w, &destMessage.h)) {
        std::cout << TTF_GetError() << std::endl;
    }

    return destMessage;
}

void renderText(const TTF_Font *font, SDL_Color color, const float x, const float y, const std::string &text) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_Surface *renderedText = TTF_RenderText_Blended(const_cast<TTF_Font *>(font), text.c_str(), color);
    GLuint texture = 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, renderedText->w, renderedText->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,renderedText->pixels);

    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(x, y);
        glTexCoord2d(20, 0); glVertex2f(x + (float)renderedText->w, y);
        glTexCoord2d(20, 20); glVertex2f(x + (float)renderedText->w, y + (float)renderedText->h);
        glTexCoord2d(0, 20); glVertex2f(x, y + (float)renderedText->h);
    glEnd();

    glDeleteTextures(1, &texture);
    SDL_FreeSurface(renderedText);
}
