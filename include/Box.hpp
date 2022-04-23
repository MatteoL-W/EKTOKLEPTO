#pragma once

class Box {
public:
    Box(int xCoord1, int yCoord1, int xCoord2, int yCoord2);

    ~Box();

    void draw();
private:
    int xCoord1, yCoord1;

    int xCoord2, yCoord2;
};