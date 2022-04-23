#pragma once

class Box {
public:
    Box(float p_xCoord1, float p_yCoord1, float p_xCoord2, float p_yCoord2)
            : xCoord1(p_xCoord1), yCoord1(p_yCoord1), xCoord2(p_xCoord2), yCoord2(p_yCoord2) {}

    ~Box();

    void draw();

private:
    float xCoord1, yCoord1;

    float xCoord2, yCoord2;
};