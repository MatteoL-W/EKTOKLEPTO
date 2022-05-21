#pragma once

class SaveManager {
public:
    SaveManager();

    ~SaveManager() = default;

    void update(int choice);

    void draw();
private:
    float x = -15, y;
};
