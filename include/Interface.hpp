#pragma once

#include <iostream>

class Interface {
public:
    virtual void handleEvents() = 0;

    virtual void update() = 0;

    virtual void render() = 0;

};
