#pragma once

class BreakScreen {
public:
    BreakScreen();

    ~BreakScreen() = default;

    void update();

    void draw();

    void drawCurrent(int choice);
};
