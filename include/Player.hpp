#pragma once

class Player {
public:
    Player(int p_type, int p_xCoord1, int p_yCoord1, int p_xCoord2, int p_yCoord2, float p_r, float p_g, float p_b)
        : type(p_type), xCoord1(p_xCoord1), yCoord1(p_yCoord1), xCoord2(p_xCoord2), yCoord2(p_yCoord2), r(p_r), g(p_g), b(p_b) {}

    ~Player();

    void draw();

private:
    int type;

    int xCoord1, yCoord1;

    int xCoord2, yCoord2;

    float r, g, b;
};