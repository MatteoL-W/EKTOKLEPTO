#pragma once

class Player {
public:
    Player(int p_type, float p_xStart, float p_yStart, float p_xEnd, float p_yEnd)
            : type(p_type), xStart(p_xStart), yStart(p_yStart), xEnd(p_xEnd), yEnd(p_yEnd) {
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

    float xStart, yStart;

    float xEnd, yEnd;

    float width, height;

    float r, g, b;
};