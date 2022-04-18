#pragma once

#include "../Game.hpp"
#include "../Interface.hpp"
#include "../Menu.hpp"

class MenuInterface : public Interface {
public:
    explicit MenuInterface(Game *game)
            : game(game), menu(new Menu()) {
    }

    ~MenuInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Game *game;

    Menu *menu;

};

