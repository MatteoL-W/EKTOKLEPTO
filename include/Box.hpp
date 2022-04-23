#pragma once

class Box {
public:
    Box(int xCoord1, int yCoord1, int xCoord2, int yCoord2)
            : xCoord1(xCoord1), yCoord1(yCoord1), xCoord2(xCoord2), yCoord2(yCoord2) {}

    ~Box();

    void draw();

private:
    int xCoord1, yCoord1;

    int xCoord2, yCoord2;
};