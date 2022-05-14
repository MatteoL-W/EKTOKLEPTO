#pragma once

#include "glm/vec2.hpp"
#include "Player.hpp"

class Zone {
public:
    Zone(int p_idChange, float xTL, float yTL, float xBR, float yBR, int p_idSwitch = -1)
            : idChange(p_idChange), TL(glm::vec2(xTL, yTL)), BR(glm::vec2(xBR, yBR)), idSwitch(p_idSwitch) {};

    ~Zone() = default;

    void draw();

    bool contains(glm::vec2 center);

    bool getIdSwitch() const { return idSwitch; };

    void applyChanges(Player* currentPlayer);

private:
    int idChange;

    glm::vec2 TL;

    glm::vec2 BR;

    int idSwitch;
};