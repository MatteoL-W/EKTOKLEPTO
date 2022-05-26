#include "../include/SaveManager.hpp"
#include "../include/tools/Text.hpp"
#include "../include/tools/utils.hpp"
#include "../include/tools/save.hpp"
#include "../include/variables/color.hpp"

Text *errorMsg;
Text *saveSaveManager;
Text *loadSaveManager;
Text *eraseSaveManager;
Text *goBackSaveManager;

Image* backgroundSaveManager;

SaveManager::SaveManager() {
    x = 50;
    backgroundSaveManager = new Image("./assets/img/menu/savemanager-background.png");
    TTF_Font *Font20 = TTF_OpenFont("./assets/fonts/HKGrotesk-Bold.ttf", 20);
    TTF_Font *Font30 = TTF_OpenFont("./assets/fonts/HKGrotesk-Bold.ttf", 30);
    TTF_Font *Font50 = TTF_OpenFont("./assets/fonts/HKGrotesk-Bold.ttf", 50);

    saveSaveManager = new Text("Sauvegarder", Font50, WhiteColor, 70, 430);
    loadSaveManager = new Text("Charger", Font50, WhiteColor, 70, 380);
    eraseSaveManager = new Text("Supprimer les sauvegardes", Font50, WhiteColor, 70, 330);
    goBackSaveManager = new Text("Retour", Font50, WhiteColor, 70, 280);

    for (int i = 0; i < 5; i++) {
        slotTexts.push_back(
                new Text("Emplacement " + std::to_string(i) + ((readSave(i).empty()) ? "" : " - niveau " + readSave(i)),
                         Font30, (readSave(i).empty()) ? WhiteColor : GreyColor, 70, 200 - i * 40));
    }

    errorMsg = new Text("No more slots available, please erase the slots", Font20, WhiteColor, 70, 10);
}

void SaveManager::update(int choice, int loadChoice) {
    if (loadChoice == -1) {
        for (int i = 1; i < 5; i++) {
            if (choice == i)
                y = 480 - i * 50 + 30;
        }
    } else {
        for (int i = 1; i < 6; i++) {
            if (loadChoice == i)
                y = 200 - i * 40 + 60;
        }
    }
}

void SaveManager::draw() {
    backgroundSaveManager->draw(glm::vec2(0,0), 1200, 720);

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
