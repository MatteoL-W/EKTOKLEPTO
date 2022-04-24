#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
                              WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    context = SDL_GL_CreateContext(window);

    if (context == nullptr) {
        std::string error = SDL_GetError();
        std::cout << "Erreur lors de la creation du contexte OpenGL";

        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    initiateWindowSize();

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
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

/**
 * @brief Chose the right interface and refresh execute its method
 */
void Engine::refresh() {
    currentInterface->update();

    // Blue background
    SDL_RenderClear(Engine::renderer);
    currentInterface->render();
    SDL_GL_SwapWindow(window);

    currentInterface->handleEvents();
}

/**
 * @brief Initiate the window size and the orthonormal coordinate system
 */
void Engine::initiateWindowSize() {
    glViewport(0, 0, Engine::WINDOW_WIDTH, Engine::WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // On définit plutôt les repère depuis le bas à gauche
    gluOrtho2D(0, GL_VIEW_SIZE, 0, GL_VIEW_SIZE);

    //float aspectRatio = Engine::WINDOW_WIDTH / (float) Engine::WINDOW_HEIGHT;

    /*if (aspectRatio > 1) {
        gluOrtho2D(
                -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
                -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    } else {
        gluOrtho2D(
                -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
                -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }*/
}
