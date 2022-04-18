#pragma once

#include "Text.hpp"

class Menu {
public:
    Menu();

    ~Menu() = default;

    void update();

    void draw();

private:
    Text *titleText;
};
