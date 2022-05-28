#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Interface.hpp"
#include "Map.hpp"
#include "tools/Music.hpp"

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

    constexpr static const float PLAYER_Y_AXIS = 0.25;

    constexpr static const float GL_VIEW_SIZE = 20.;

    static SDL_Renderer *renderer;

    static Music *ambianceMusic;

    void setRunning(bool newState) { isRunning = newState; }

    bool running() const { return isRunning; };

    static void initiateWindowSize();

    //Activity Handle
    void setCurrentInterface(Interface* activity) { currentInterface = activity; };

    void startGame(int level = 0);

    void displayMenu();

    void displayEnd();

    void resumeGame();

    void openSaveManager(Interface* currentActivity);

private:
    SDL_Window *window;

    SDL_GLContext context;

    bool isRunning = false;

    Interface *currentInterface;

    static void initiateSDLLibs() ;

    static void startMusic();

};
