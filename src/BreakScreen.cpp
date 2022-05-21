#include "../include/BreakScreen.hpp"
#include "../include/tools/Text.hpp"
#include "../include/variables/Color.hpp"

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
    saveBreak = new Text("SAVE (MAX 5 SAVES)", Press500, WhiteColor, -6.5, 1);
    eraseSavesBreak = new Text("ERASE ALL SAVES", Press500, WhiteColor, -6.5, 0);
    quitBreak = new Text("QUIT", Press500, WhiteColor, -6.5, -1);
}

void BreakScreen::update() {

}

void BreakScreen::draw() {
    titleBreak->draw();
    resumeBreak->draw();
    saveBreak->draw();
    eraseSavesBreak->draw();
    quitBreak->draw();
}

void BreakScreen::drawCurrent(int choice) {
    glDisable(GL_BLEND);

    float x = -7.5, y;
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
        case 4:
            y = -1;
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
