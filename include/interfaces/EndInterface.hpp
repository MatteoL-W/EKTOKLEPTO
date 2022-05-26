#pragma once

#include "../Engine.hpp"
#include "../Interface.hpp"
#include "../End.hpp"

class EndInterface : public Interface {
public:
    explicit EndInterface(Engine *engine)
            : engine(engine), end(new End()) {
    }

    ~EndInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Engine *engine;

    End *end;
};

