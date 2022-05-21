#include "../include/SaveManager.hpp"
#include "../include/tools/Text.hpp"
#include "../include/tools/utils.hpp"
#include "../include/variables/color.hpp"

Text* titleSaveManager;
Text* saveSaveManager;
Text* loadSaveManager;
Text* eraseSaveManager;
Text* goBackSaveManager;

SaveManager::SaveManager() {
    TTF_Font* Press500 = TTF_OpenFont("./assets/fonts/Press.ttf", 500);
    TTF_Font* Press800 = TTF_OpenFont("./assets/fonts/Press.ttf", 800);

    titleSaveManager = new Text("SAVE MANAGER", Press800, WhiteColor, -7.5, 5);
    saveSaveManager = new Text("SAVE", Press500, WhiteColor, -14, 2);
    loadSaveManager = new Text("LOAD", Press500, WhiteColor, -14, 1);
    eraseSaveManager = new Text("ERASE ALL SAVES", Press500, WhiteColor, -14, 0);
    goBackSaveManager = new Text("CANCEL", Press500, WhiteColor, -14, -1);
}

void SaveManager::update(int choice) {
    switch (choice) {
        case 1:
            y = 2;
            break;
        case 2:
            y = 1;
            break;
        case 3:
            y = 0;
            break;
        case 4:
            y = -1;
            break;
        default:
            break;
    }
}

void SaveManager::draw() {
    titleSaveManager->draw();
    saveSaveManager->draw();
    loadSaveManager->draw();
    eraseSaveManager->draw();
    goBackSaveManager->draw();

    drawCurrentSquare(x, y);
}
