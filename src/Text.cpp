#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../include/Game.hpp"
#include "../include/Text.hpp"

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
    Text::texture = SDL_CreateTextureFromSurface(Game::renderer, Text::surface);
    Text::destRect = createDestRect(Text::font, Text::message, 0, 0);
}

/**
 * @brief Draw the text
 */
void Text::draw() {
    SDL_RenderCopy(Game::renderer, Text::texture, NULL, &(Text::destRect));
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
    Text::texture = SDL_CreateTextureFromSurface(Game::renderer, Text::surface);
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
    Text::texture = SDL_CreateTextureFromSurface(Game::renderer, Text::surface);
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