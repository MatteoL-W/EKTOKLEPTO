#pragma once

#include "tools/Text.hpp"
#include "tools/utils.hpp"

class Menu {
public:
    Menu();

    ~Menu() = default;

    void update();

    void draw();
};
