#include <SDL2/SDL_image.h>
#include "../include/Menu.hpp"
#include "../include/variables/color.hpp"
#include "../include/tools/Image.hpp"

Text *playButton;
Text *loadButton;
Text *quitButton;

Image* backgroundMenu;
Image* ektoklepto;
float yEktoklepto = 100;
bool goingDown = true;

Menu::Menu() {
    backgroundMenu = new Image("./assets/img/menu/menu-background.png");
    ektoklepto = new Image("./assets/img/menu/ektoklepto.png");
    TTF_Font* Font500 = TTF_OpenFont("./assets/fonts/HKGrotesk-Bold.ttf", 50);

    playButton = new Text("Jouer", Font500, WhiteColor, 140, 420);
    loadButton = new Text("Sauvegardes", Font500, WhiteColor, 140, 350);
    quitButton = new Text("Quitter", Font500, WhiteColor, 140, 280);
}

void Menu::update() {
    if (goingDown) {
        if (yEktoklepto > 50) {
            yEktoklepto *= 0.993;
        }
        if (yEktoklepto < 50) {
            goingDown = false;
            return;
        }
    }

    if (!goingDown) {
        if (yEktoklepto > 100) {
            goingDown = true;
            return;
        }
        if (yEktoklepto < 100) {
            yEktoklepto *= 1.01;
        }
    }

}

void Menu::draw() {
    glClearColor(0.18, 0.5, 0.41, 1);

    backgroundMenu->draw(glm::vec2(0,0), 1200, 720);
    ektoklepto->draw(glm::vec2(600, yEktoklepto), 500, 458.66);

    playButton->draw();
    loadButton->draw();
    quitButton->draw();
}
