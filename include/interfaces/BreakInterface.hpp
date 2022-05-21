#pragma once

#include "../Engine.hpp"
#include "../Interface.hpp"
#include "../BreakScreen.hpp"

class BreakInterface : public Interface {
public:
    explicit BreakInterface(Engine *engine)
            : engine(engine), breakScreen(new BreakScreen()) {
    }

    ~BreakInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Engine *engine;

    BreakScreen *breakScreen;

    void handleRequest();
};

