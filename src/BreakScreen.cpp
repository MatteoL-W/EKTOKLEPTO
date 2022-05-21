#include "../include/BreakScreen.hpp"
#include "../include/tools/Text.hpp"
#include "../include/tools/utils.hpp"
#include "../include/variables/color.hpp"

Text* titleBreak;
Text* resumeBreak;
Text* saveBreak;
Text* eraseSavesBreak;
Text* quitBreak;

BreakScreen::BreakScreen() {
    TTF_Font* Press500 = TTF_OpenFont("./assets/fonts/Press.ttf", 500);
    TTF_Font* Press800 = TTF_OpenFont("./assets/fonts/Press.ttf", 800);

    titleBreak = new Text("THOMAS WAS DRUNK", Press800, WhiteColor, -7.5, 5);
    resumeBreak = new Text("RESUME", Press500, WhiteColor, -6.5, 2);
    saveBreak = new Text("OPEN SAVE MANAGER", Press500, WhiteColor, -6.5, 1);
    quitBreak = new Text("QUIT", Press500, WhiteColor, -6.5, 0);
}

void BreakScreen::update(int choice) {
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
        default:
            break;
    }
}

void BreakScreen::draw() {
    titleBreak->draw();
    resumeBreak->draw();
    saveBreak->draw();
    quitBreak->draw();

    drawCurrentSquare(x, y);
}
