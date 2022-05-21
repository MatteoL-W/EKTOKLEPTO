#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Interface.hpp"
#include "Map.hpp"

class Engine {
public:
    Engine();

    ~Engine();

    void clean();

    void refresh();

    SDL_Event event;

    static const int WINDOW_WIDTH = 1200;

    static const int WINDOW_HEIGHT = 750;

    constexpr static const float aspectRatio = Engine::WINDOW_WIDTH / (float) Engine::WINDOW_HEIGHT;

    static SDL_Renderer *renderer;

    void setRunning(bool newState) { isRunning = newState; }

    bool running() const { return isRunning; };

    static void initiateWindowSize();

    //Activity Handle
    void startGame(int level = 0);

    void displayMenu();

    void resumeGame();

    void openSaveManager();

private:
    SDL_Window *window;

    SDL_GLContext context;

    bool isRunning = false;

    Interface *currentInterface;

};
