#pragma once

#include "../Engine.hpp"
#include "../Interface.hpp"
#include "../BreakScreen.hpp"

class SaveManagerInterface : public Interface {
public:
    explicit SaveManagerInterface(Engine *engine)
            : engine(engine) {
    }

    ~SaveManagerInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Engine *engine;
};

