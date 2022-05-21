#include "../include/interfaces/SaveManagerInterface.hpp"

enum ChoiceSave {
    save = 1, load, eraseAll, goBack
};
const int MAX_CHOICES_SAVE = 4;
ChoiceSave currentChoiceSave = save;

void SaveManagerInterface::handleEvents() {
    SDL_Event event = engine->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        engine->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_1:
                currentChoiceSave = save;
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
                                    static_cast<ChoiceSave>(static_cast<int>(currentChoiceSave) + 1) : save;
                break;

            case SDLK_RETURN:
                //handleRequest();
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
