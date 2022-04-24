#pragma once

#include "glm/vec2.hpp"

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), positionStart(p_xStart, p_yStart), positionEnd(p_xEnd, p_yEnd) {
        switch (type) {
            case 1:
                width = 1;
                height = 1;
                r = 0;
                g = 1;
                b = 0;
        }
    }

    ~Player();

    void draw();

    void drawEndPlace();

private:
    int type;

    glm::vec2 positionStart;

    glm::vec2 positionEnd;

    float width, height;

    float r, g, b;
};