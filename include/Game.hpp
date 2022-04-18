#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Interface.hpp"

class Game {
public:
    Game();

    ~Game();

    void clean();

    void refresh();

    SDL_Event event;

    static const int WINDOW_WIDTH = 750;

    static const int WINDOW_HEIGHT = 750;

    static SDL_Renderer *renderer;

    void setRunning(bool newState) { isRunning = newState; }

    bool running() { return isRunning; };

    Interface *getCurrentInterface() { return currentInterface; };

private:
    SDL_Window *window;

    bool isRunning = false;

    Interface *currentInterface;
};
