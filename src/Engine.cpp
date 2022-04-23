#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../include/Engine.hpp"
#include "../include/interfaces/MenuInterface.hpp"
#include "../include/interfaces/GameInterface.hpp"

SDL_Renderer *Engine::renderer = nullptr;

MenuInterface *menuInterface = nullptr;
GameInterface *gameInterface = nullptr;

/**
 * @brief Initialize the engine (assign the window, renderer, define the engine as running)
 */
Engine::Engine() {
    /* Vérifications */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "IMG_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "TTF_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Create SDL needs */
    window = SDL_CreateWindow("Thomas Was Alone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    /* Define the interfaces */
    menuInterface = new MenuInterface(this);
    gameInterface = new GameInterface(this);

    /* Define the default interface*/
    currentInterface = gameInterface;

    isRunning = true;
}

Engine::~Engine() = default;

/**
 * @brief Quit the engine properly
 */
void Engine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

/**
 * @brief Refresh the engine and chose the right interface
 */
void Engine::refresh() {
    currentInterface->handleEvents();
    currentInterface->update();
    currentInterface->render();
}
