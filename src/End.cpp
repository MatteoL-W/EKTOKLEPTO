#include <SDL2/SDL_image.h>
#include "../include/End.hpp"
#include "../include/tools/Image.hpp"

Image* backgroundEnd;
Image* ektokleptoEnd;

End::End() {
    backgroundEnd = new Image("./assets/img/menu/menu-background.png");
    ektokleptoEnd = new Image("./assets/img/menu/ektoklepto.png");
}

void End::update() {
}

void End::draw() {
    glClearColor(0.18, 0.5, 0.41, 1);

    backgroundEnd->draw(glm::vec2(0,0), 1200, 720);
    ektokleptoEnd->draw(glm::vec2(600, 40), 500, 458.66);
}
