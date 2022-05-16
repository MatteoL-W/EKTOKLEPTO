#pragma once

#include "../Engine.hpp"
#include "../Interface.hpp"
#include "../Game.hpp"

class GameInterface : public Interface {
public:
    explicit GameInterface(Engine *engine)
            : engine(engine), game(new Game()), currentMap(this->game->getMap()), camera(this->game->getCamera()) {
        game->setMap(0);
        // mettre ça dans le change interface
    }

    ~GameInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Engine *engine;

    Game *game;

    Map *currentMap;

    Camera *camera;
};

