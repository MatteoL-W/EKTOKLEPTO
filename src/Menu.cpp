#include <SDL2/SDL.h>
#include "../include/Menu.hpp"
#include "../include/Engine.hpp"
#include "../include/tools/Text.hpp"
#include "../include/variables/Color.hpp"

Menu::Menu() {
    //titleText = new Text();
    //titleText->create("Welcome in the menu", WhiteColor, "Press");
    /*titleText->changeDestRect(
            getPadding(Engine::WINDOW_WIDTH, titleText->getDestRect().w),
            getPadding(Engine::WINDOW_HEIGHT, titleText->getDestRect().h)
    );*/
}

void Menu::update() {

}

void Menu::draw() {
    //titleText->draw();
    RenderText(TTF_OpenFont("./assets/fonts/Press.ttf", 2), 1, 0, 0, 1, 1, 1, "Test");
}