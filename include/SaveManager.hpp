#pragma once

#include <vector>
#include "tools/Text.hpp"

class SaveManager {
public:
    SaveManager();

    ~SaveManager() = default;

    void update(int choice, int loadChoice);

    void draw();

    void setSlotMessageActivity(bool newActivity) { noSlotsMsg = newActivity; };

    std::vector<Text *> getLevelsText() { return slotTexts; };

private:
    float x, y;

    std::vector<Text *> slotTexts;

    bool noSlotsMsg = false;
};
