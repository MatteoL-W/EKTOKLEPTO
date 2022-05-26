#pragma once

#include "glm/vec2.hpp"

class BreakScreen {
public:
    BreakScreen();

    ~BreakScreen() = default;

    void update(int choice);

    void draw();

private:
    float x = 670, y;
};
