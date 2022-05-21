#include "../include/interfaces/SaveManagerInterface.hpp"
#include "../../include/Game.hpp"
#include "../../include/tools/save.hpp"

enum ChoiceSave {
    saveGame = 1, load, eraseAll, goBack
};
const int MAX_CHOICES_SAVE = 4;
ChoiceSave currentChoiceSave = saveGame;

void SaveManagerInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_1:
                currentChoiceSave = saveGame;
                break;
            case SDLK_2:
                currentChoiceSave = load;
                break;
            case SDLK_3:
                currentChoiceSave = eraseAll;
                break;
            case SDLK_4:
                currentChoiceSave = goBack;
                break;

            case SDLK_TAB:
                currentChoiceSave = (currentChoiceSave < MAX_CHOICES_SAVE) ?
                                    static_cast<ChoiceSave>(static_cast<int>(currentChoiceSave) + 1) : saveGame;
                break;

            case SDLK_RETURN:
                handleRequest();
                break;
        }
    }
}

void SaveManagerInterface::update() {
    saveManager->update(currentChoiceSave);
}

void SaveManagerInterface::render() {
    saveManager->draw();
}

void SaveManagerInterface::handleRequest() {
    switch (currentChoiceSave) {
        case saveGame:
            if (getSlotUsedAmount() < 5)
                save(std::to_string(Game::level));
            else {
                std::cout << "can't save !!!";
            }
            break;
        case load:
            // get the wanted save to load
            engine->startGame(stoi(readSave(0)));
            break;
        case eraseAll:
            eraseSaves();
            break;
        case goBack:
            // get the last activity and change to it
            break;
    }
}
