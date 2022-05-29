#pragma once

#include "../Engine.hpp"
#include "../Interface.hpp"
#include "../Menu.hpp"

class MenuInterface : public Interface {
public:
    explicit MenuInterface(Engine *engine)
            : engine(engine), menu(new Menu()) {
        setButtonCoordinates();
    }

    ~MenuInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    void setButtonCoordinates();

    Engine *engine;

    Menu *menu;

    std::pair<glm::vec2, glm::vec2> start;
    std::pair<glm::vec2, glm::vec2> load;
    std::pair<glm::vec2, glm::vec2> quit;
};

