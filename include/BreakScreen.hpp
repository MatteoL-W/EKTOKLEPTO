#pragma once

class BreakScreen {
public:
    BreakScreen();

    ~BreakScreen() = default;

    void update(int choice);

    void draw();

private:
    float x = -7.5, y;
};