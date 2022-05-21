#include "../include/interfaces/SaveManagerInterface.hpp"
#include "../../include/Game.hpp"
#include "../../include/tools/save.hpp"
#include "../../include/variables/color.hpp"

enum ChoiceSave {
    saveGame = 1, load, eraseAll, goBack
};
const int MAX_CHOICES_SAVE = 4;
ChoiceSave currentChoiceSave = saveGame;
int currentLoadSave = -1;

int SDLKeyTo5[5] = {SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5};

void SaveManagerInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        if (!choosingLevelToLoad)
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
        else {
            // Set associated slot when load is selected
            for (int i = 0; i < 5; i++) {
                if (event.key.keysym.sym == SDLKeyTo5[i] && i >= getSlotUsedAmount()) {
                    currentLoadSave = i+1;
                    std::cout << currentLoadSave;
                }
            }

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    choosingLevelToLoad = false;
                    currentLoadSave = -1;
                    break;
                case SDLK_RETURN:
                    handleRequest();
                    break;
                case SDLK_TAB:
                    currentLoadSave = (currentLoadSave < 5) ? currentLoadSave + 1 : 1;
                    break;
            }
        }
    }
}


void SaveManagerInterface::update() {
    saveManager->update(currentChoiceSave, currentLoadSave);
}

void SaveManagerInterface::render() {
    saveManager->draw();
}

void SaveManagerInterface::handleRequest() {
    if (currentChoiceSave == load && currentLoadSave == -1) {
        choosingLevelToLoad = true;
        currentLoadSave = getSlotUsedAmount() + 1;
        return;
    }

    switch (currentChoiceSave) {
        case saveGame:
            if (getSlotUsedAmount() < 5) {
                save(std::to_string(Game::level));
                refreshSaveManagerTexts();
            }
            else {
                std::cout << "No more slots available, please erase all the slots" << std::endl;
                // ToDo
            }
            break;

        case load:
            engine->startGame(stoi(readSave(currentLoadSave)));
            break;

        case eraseAll:
            eraseSaves();
            refreshSaveManagerTexts();
            break;

        case goBack:
            engine->resumeGame();
            break;
    }
}

void SaveManagerInterface::refreshSaveManagerTexts() {
    std::vector<Text*> texts = saveManager->getLevelsText();
    for (size_t i = 0; i < texts.size(); i++) {
        texts[i]->deleteTexture();
        texts[i]->changeColor((readSave(i).empty()) ? WhiteColor : GreyColor);
        texts[i]->changeText("EMPLACEMENT " + std::to_string(i) + " - NIVEAU " + readSave(i));
        texts[i]->apply();
    }
}
