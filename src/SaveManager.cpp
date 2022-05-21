#include "../include/SaveManager.hpp"
#include "../include/tools/Text.hpp"
#include "../include/tools/utils.hpp"
#include "../include/tools/save.hpp"
#include "../include/variables/color.hpp"

Text *errorMsg;
Text *titleSaveManager;
Text *saveSaveManager;
Text *loadSaveManager;
Text *eraseSaveManager;
Text *goBackSaveManager;

SaveManager::SaveManager() {
    TTF_Font *Press200 = TTF_OpenFont("./assets/fonts/Press.ttf", 200);
    TTF_Font *Press300 = TTF_OpenFont("./assets/fonts/Press.ttf", 300);
    TTF_Font *Press500 = TTF_OpenFont("./assets/fonts/Press.ttf", 500);
    TTF_Font *Press800 = TTF_OpenFont("./assets/fonts/Press.ttf", 800);

    titleSaveManager = new Text("SAVE MANAGER", Press800, WhiteColor, -7.5, 5);
    saveSaveManager = new Text("SAVE", Press500, WhiteColor, -14, 2);
    loadSaveManager = new Text("LOAD", Press500, WhiteColor, -14, 1);
    eraseSaveManager = new Text("ERASE ALL SAVES", Press500, WhiteColor, -14, 0);
    goBackSaveManager = new Text("CANCEL", Press500, WhiteColor, -14, -1);

    for (int i = 0; i < 5; i++) {
        slotTexts.push_back(
                new Text("EMPLACEMENT " + std::to_string(i) + ((readSave(i).empty()) ? "" : " - NIVEAU " + readSave(i)),
                         Press300, (readSave(i).empty()) ? WhiteColor : GreyColor, 1, 2 - i));
    }

    errorMsg = new Text("No more slots available, please erase the slots", Press200, WhiteColor, -14, -6);
}

void SaveManager::update(int choice, int loadChoice) {
    if (loadChoice == -1) {
        x = -15;
        for (int i = 1; i < 5; i++) {
            if (choice == i)
                y = 2 - i + 1;
        }
    } else {
        x = 0;
        for (int i = 1; i < 6; i++) {
            if (loadChoice == i)
                y = 2 - i + 1;
        }
    }
}

void SaveManager::draw() {
    titleSaveManager->draw();
    saveSaveManager->draw();
    loadSaveManager->draw();
    eraseSaveManager->draw();
    goBackSaveManager->draw();

    for (auto &slot: slotTexts) {
        slot->draw();
    }

    if (noSlotsMsg)
        errorMsg->draw();

    drawCurrentSquare(x, y);
}
