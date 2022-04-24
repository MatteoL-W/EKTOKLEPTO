#pragma once

#include "tools/Text.hpp"

class Menu {
public:
    Menu();

    ~Menu() = default;

    void update();

    void draw();

private:
    Text *titleText;
};
