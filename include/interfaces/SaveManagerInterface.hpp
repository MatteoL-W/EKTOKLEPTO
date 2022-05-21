#pragma once

#include "../Engine.hpp"
#include "../Interface.hpp"
#include "../SaveManager.hpp"

class SaveManagerInterface : public Interface {
public:
    explicit SaveManagerInterface(Engine *engine)
            : engine(engine), saveManager(new SaveManager()) {
    }

    ~SaveManagerInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

    void setPreviousActivity(Interface* p_previousActivity) { previousActivity = p_previousActivity; };

private:
    Engine *engine;

    SaveManager* saveManager;

    void handleRequest();

    bool choosingLevelToLoad;

    void refreshSaveManagerTexts() ;

    Interface* previousActivity;
};

