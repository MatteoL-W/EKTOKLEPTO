#pragma once

#include "glm/vec2.hpp"
#include "Player.hpp"

enum Changes {
    ReverseGravity = 1, Mini, Maxi, Jump
};

class Zone {
public:
    Zone(int p_idChange, float xTL, float yTL, float xBR, float yBR, int p_idSwitch = -1)
            : idChange(p_idChange), TL(glm::vec2(xTL, yTL)), BR(glm::vec2(xBR, yBR)), idSwitch(p_idSwitch) {
        initValues();
    };

    ~Zone() = default;

    void draw();

    void initValues();

    bool contains(glm::vec2 playerBL, glm::vec2 playerBR);

    int getIdChange() const { return idChange; }

    int getIdSwitch() const { return idSwitch; };

    void applyChanges(Player *currentPlayer);

    int getId() const { return idChange; };

private:
    int idChange;

    glm::vec2 TL;

    glm::vec2 BR;

    int idSwitch;

    float r, g, b;
};