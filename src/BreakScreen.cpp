#include "../include/BreakScreen.hpp"
#include "../include/tools/Text.hpp"
#include "../include/tools/Image.hpp"
#include "../include/tools/utils.hpp"
#include "../include/variables/color.hpp"

Image* backgroundBreak;
Text* resumeBreak;
Text* saveBreak;
Text* quitBreak;

BreakScreen::BreakScreen() {
    backgroundBreak = new Image("./assets/img/menu/break-background.png");
    TTF_Font* Font50 = TTF_OpenFont("./assets/fonts/HKGrotesk-Bold.ttf", 50);

    resumeBreak = new Text("Reprendre", Font50, WhiteColor, 700, 200);
    saveBreak = new Text("Sauvegardes", Font50, WhiteColor, 700, 130);
    quitBreak = new Text("Quitter", Font50, WhiteColor, 700, 60);
}

void BreakScreen::update(int choice) {
    switch (choice) {
        case 1:
            y = 230;
            break;
        case 2:
            y = 160;
            break;
        case 3:
            y = 90;
            break;
        default:
            break;
    }
}

void BreakScreen::draw() {
    backgroundBreak->draw(glm::vec2(0,0), 1200, 720);

    resumeBreak->draw();
    saveBreak->draw();
    quitBreak->draw();

    drawCurrentSquare(x, y);
}
