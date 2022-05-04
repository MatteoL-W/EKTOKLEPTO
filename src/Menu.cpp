#include <SDL2/SDL.h>
#include "../include/Menu.hpp"
#include "../include/Engine.hpp"
#include "../include/tools/Text.hpp"
#include "../include/variables/Color.hpp"

Text *textTest;

Menu::Menu() {
    textTest = new Text("ok sa march", TTF_OpenFont("./assets/fonts/Press.ttf", 500), WhiteColor, 1, 1);
}

void Menu::update() {

}

void Menu::draw() {
    textTest->draw();
}