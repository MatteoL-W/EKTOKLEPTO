#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Interface.hpp"

class Engine {
public:
    Engine();

    ~Engine();

    void clean();

    void refresh();

    SDL_Event event;

    static const int WINDOW_WIDTH = 750;

    static const int WINDOW_HEIGHT = 750;

    constexpr static const float GL_VIEW_SIZE = 20.;

    static SDL_Renderer *renderer;

    void setRunning(bool newState) { isRunning = newState; }

    bool running() const { return isRunning; };

    Interface *getCurrentInterface() { return currentInterface; };

private:
    SDL_Window *window;

    SDL_GLContext context;

    bool isRunning = false;

    Interface *currentInterface;

    static void initiateWindowSize();
};
