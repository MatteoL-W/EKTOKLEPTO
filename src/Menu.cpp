#include "../include/Menu.hpp"
#include "../include/variables/Color.hpp"

Text *title;
Text *playButton;
Text *loadButton;
Text *quitButton;

Menu::Menu() {
    TTF_Font* Press800 = TTF_OpenFont("./assets/fonts/Press.ttf", 800);
    TTF_Font* Press500 = TTF_OpenFont("./assets/fonts/Press.ttf", 500);

    title = new Text("Menu", Press800, WhiteColor, -2.2, 6);
    playButton = new Text("Start a new game", Press500, WhiteColor, -10, 2);
    loadButton = new Text("Load a saved game", Press500, WhiteColor, -10, 0);
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
}

void Menu::drawCurrent(int choice) {
    glDisable(GL_BLEND);
    float x = -11, y;
    switch (choice) {
        case 1:
            y = 2;
            break;
        case 2:
            y = 0;
            break;
        case 3:
            y = -2;
            break;
        default:
            break;
    }

    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(x, y + 0.35, 0);
        glRotatef(45,0,0,1);

        glBegin(GL_QUADS);
            glVertex2f(0.25, 0.25);
            glVertex2f(-0.25, 0.25);
            glVertex2f(-0.25, -0.25);
            glVertex2f(0.25, -0.25);
        glEnd();
    glPopMatrix();
}
