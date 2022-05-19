#include "../include/BreakScreen.hpp"
#include "../include/tools/Text.hpp"
#include "../include/variables/Color.hpp"

Text* titleBreak;
Text* saveBreak;
Text* eraseSavesBreak;
Text* quitBreak;

BreakScreen::BreakScreen() {
    TTF_Font* Press500 = TTF_OpenFont("./assets/fonts/Press.ttf", 500);
    TTF_Font* Press800 = TTF_OpenFont("./assets/fonts/Press.ttf", 800);

    titleBreak = new Text("THOMAS WAS DRUNK", Press800, WhiteColor, -7.5, 4);
    saveBreak = new Text("SAVE (MAX 5 SAVES)", Press500, WhiteColor, -6.5, 1);
    eraseSavesBreak = new Text("ERASE ALL SAVES", Press500, WhiteColor, -6.5, 0);
    quitBreak = new Text("QUIT", Press500, WhiteColor, -6.5, -1);
}

void BreakScreen::update() {

}

void BreakScreen::draw() {
    titleBreak->draw();
    saveBreak->draw();
    eraseSavesBreak->draw();
    quitBreak->draw();
}