#include <SDL2/SDL_image.h>
#include "../include/End.hpp"
#include "../include/tools/Image.hpp"
#include "../include/tools/draw.hpp"

Image *backgroundEnd;
Image *ektokleptoEnd;
bool goingForward = true;
float backgroundWidth = 1200, backgroundHeight = 720, backgroundStartingX = 0, backgroundStartingY = 0;
float ektoWidth = 500, ektoHeight = 458.66, ektoStartingX = 600, ektoStartingY = 100;
float opacity = 0;

End::End() {
    backgroundEnd = new Image("./assets/img/end/louvre.png");
    ektokleptoEnd = new Image("./assets/img/menu/ektoklepto.png");
}

void End::update() {
    if (goingForward) {
        backgroundWidth *= 0.9999;
        backgroundHeight *= 0.9999;
        ektoWidth *= 1.005;
        ektoHeight *= 1.005;
        ektoStartingX -= 5;
        ektoStartingY -= 3;

        if (ektoWidth > 1283) {
            opacity = (opacity < 1) ? opacity + 0.001 : 1;
        }
    }
}

void End::draw() {
    if (opacity == 0) {
        backgroundEnd->draw(
                glm::vec2(backgroundStartingX, backgroundStartingY),
                backgroundWidth,
                backgroundHeight
        );

        ektokleptoEnd->draw(
                glm::vec2(ektoStartingX, ektoStartingY),
                ektoWidth,
                ektoHeight
        );
    }

    else {
        glColor4f(1, 1, 1, 1);
        drawRect(glm::vec2(0, 720), glm::vec2(1200, 0));
    }
}
