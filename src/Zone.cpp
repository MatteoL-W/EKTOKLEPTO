#include "../include/Zone.hpp"
#include "../include/tools/draw.hpp"

void Zone::draw() {
    drawRect(TL, BR, true);
}
