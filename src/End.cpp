#include <SDL2/SDL_image.h>
#include "../include/End.hpp"
#include "../include/tools/Image.hpp"
#include "../include/tools/draw.hpp"

Image *backgroundEnd;
Image *screenEnd;
Image *ektokleptoEnd;
bool goingForward = true, secondImage = false;
float backgroundWidth = 1200, backgroundHeight = 720, backgroundStartingX = 0, backgroundStartingY = 0;
float ektoWidth = 500, ektoHeight = 458.66, ektoStartingX = 600, ektoStartingY = 100;
float opacity = 0;

End::End() {
    screenEnd = new Image("./assets/img/end/end-background.png");
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

        if (ektoWidth > 3080) {
            secondImage = true;
        }
    }
}

void End::draw() {
    if (!secondImage) {
        backgroundEnd->draw(
                glm::vec2(backgroundStartingX, backgroundStartingY),
                backgroundWidth,
                backgroundHeight
        );
    } else {
        screenEnd->draw(glm::vec2(0,0), 1200, 720);
    }

    ektokleptoEnd->draw(
            glm::vec2(ektoStartingX, ektoStartingY),
            ektoWidth,
            ektoHeight
    );
}
