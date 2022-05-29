#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "../include/Engine.hpp"
#include "../include/interfaces/MenuInterface.hpp"
#include "../include/interfaces/GameInterface.hpp"
#include "../include/interfaces/BreakInterface.hpp"
#include "../include/interfaces/SaveManagerInterface.hpp"
#include "../include/interfaces/EndInterface.hpp"
#include "../include/tools/Sound.hpp"

SDL_Renderer *Engine::renderer = nullptr;
Music *Engine::ambianceMusic = nullptr;

MenuInterface *menuInterface = nullptr;
BreakInterface *breakInterface = nullptr;
GameInterface *gameInterface = nullptr;
SaveManagerInterface *saveManagerInterface = nullptr;
EndInterface *endInterface = nullptr;

/**
 * @brief Initialize the engine (assign the window, renderer, define the engine as running)
 */
Engine::Engine() {
    initiateSDLLibs();

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

    /* Define the interfaces */
    menuInterface = new MenuInterface(this);
    breakInterface = new BreakInterface(this);
    gameInterface = new GameInterface(this);
    saveManagerInterface = new SaveManagerInterface(this);
    endInterface = new EndInterface(this);

    /* Define the default interface*/
    currentInterface = menuInterface;

    isRunning = true;

    initiateWindowSize();
    startMusic();
}

void Engine::initiateSDLLibs() {
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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
}

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

    SDL_RenderClear(Engine::renderer);
    glClear(GL_COLOR_BUFFER_BIT);
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

    gluOrtho2D(
            0, 1200,
            0, 720
    );
}

void Engine::startGame(int level) {
    Game::level = level;
    currentInterface = gameInterface;
    gameInterface->updateLevel();
}

void Engine::displayMenu() {
    currentInterface = breakInterface;
}

void Engine::resumeGame() {
    currentInterface = gameInterface;
}

void Engine::openSaveManager(Interface *currentActivity) {
    currentInterface = saveManagerInterface;
    saveManagerInterface->setPreviousActivity(currentActivity);
}

void Engine::startMusic() {
    ambianceMusic = new Music("./assets/sounds/ambiance.wav");
    ambianceMusic->play(-1);
}

void Engine::displayEnd() {
    Music::stop();
    currentInterface = endInterface;
    initiateWindowSize();

    Mix_Volume(-1, MIX_MAX_VOLUME);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 8);

    ambianceMusic = nullptr;
    ambianceMusic = new Music("./assets/sounds/wont_stop.wav");
    ambianceMusic->play(-1);

    auto *policeSound = new Sound("./assets/sounds/police.wav");
    policeSound->play();
}
