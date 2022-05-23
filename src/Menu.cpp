#include <SDL2/SDL_image.h>
#include "../include/Menu.hpp"
#include "../include/variables/color.hpp"
#include "../include/tools/Image.hpp"

Text *title;
Text *playButton;
Text *loadButton;
Text *quitButton;

Image* backgroundMenu;

Menu::Menu() {
    backgroundMenu = new Image("./assets/img/thomas_test.png", -6, -6, 50);
    TTF_Font* Press800 = TTF_OpenFont("./assets/fonts/Press.ttf", 800);
    TTF_Font* Press500 = TTF_OpenFont("./assets/fonts/Press.ttf", 500);

    title = new Text("Menu", Press800, WhiteColor, -2.2, 6);
    playButton = new Text("Start a new game", Press500, WhiteColor, -10, 2);
    loadButton = new Text("Open the Save Manager", Press500, WhiteColor, -10, 0);
    quitButton = new Text("Quit the game", Press500, WhiteColor, -10, -2);
}

void Menu::update() {

}

void Menu::draw() {
    glClearColor(0.18, 0.5, 0.41, 1);

    title->draw();
    playButton->draw();
    loadButton->draw();
    quitButton->draw();

    backgroundMenu->draw();
}
