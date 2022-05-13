#include "../include/Zone.hpp"
#include "../include/tools/draw.hpp"

void Zone::draw() {
    drawRect(TL, BR, true);
}

bool Zone::contains(glm::vec2 center) {
    if ((TL.x < center.x && center.x < BR.x) && (BR.y < center.y && center.y < TL.y)) {
        return true;
    }
    return false;
}


