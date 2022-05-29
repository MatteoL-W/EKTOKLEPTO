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

int SDLKeyTo5[5] = {SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4};

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
                case SDLK_DOWN:
                    currentChoiceSave = (currentChoiceSave < MAX_CHOICES_SAVE) ?
                                        static_cast<ChoiceSave>(static_cast<int>(currentChoiceSave) + 1) : saveGame;
                    break;

                case SDLK_UP:
                    currentChoiceSave = (currentChoiceSave > 1) ?
                                        static_cast<ChoiceSave>(static_cast<int>(currentChoiceSave) - 1) : goBack;
                    break;

                case SDLK_RETURN:
                    handleRequest();
                    break;
                case SDLK_ESCAPE:
                    engine->setCurrentInterface(previousActivity);
                    break;
            }
            // Chosing level to load
        else {
            // Set associated slot when load is selected
            for (int i = 0; i < getSlotUsedAmount(); i++) {
                if (event.key.keysym.sym == SDLKeyTo5[i]) {
                    currentLoadSave = i + 1;
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
                    currentLoadSave = (currentLoadSave < getSlotUsedAmount()) ? currentLoadSave + 1 : 1;
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
        if (getSlotUsedAmount() != 0) {
            choosingLevelToLoad = true;
            currentLoadSave = 1;
        }
        return;
    }

    switch (currentChoiceSave) {
        case saveGame:
            if (getSlotUsedAmount() < 5) {
                save(std::to_string(Game::level));
                refreshSaveManagerTexts();
            } else {
                saveManager->setSlotMessageActivity(true);
            }
            break;

        case load:
            engine->startGame(std::stoi(readSave(currentLoadSave - 1)));
            choosingLevelToLoad = false;
            currentLoadSave = -1;
            break;

        case eraseAll:
            eraseSaves();
            saveManager->setSlotMessageActivity(false);
            refreshSaveManagerTexts();
            break;

        case goBack:
            engine->setCurrentInterface(previousActivity);
            break;
    }
}

void SaveManagerInterface::refreshSaveManagerTexts() {
    std::vector<Text *> texts = saveManager->getLevelsText();
    for (size_t i = 0; i < texts.size(); i++) {
        texts[i]->deleteTexture();
        texts[i]->changeColor((readSave(i).empty()) ? WhiteColor : GreyColor);
        texts[i]->changeText(
                "Emplacement " + std::to_string(i) + ((readSave(i).empty()) ? "" : " - niveau " + readSave(i)));
        texts[i]->apply();
    }
}
