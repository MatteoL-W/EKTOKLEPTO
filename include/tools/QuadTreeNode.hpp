#pragma once

#include <vector>
#include "../Box.hpp"


struct QuadTreeNode {
    QuadTreeNode* topLeft;
    QuadTreeNode* topRight;
    QuadTreeNode* bottomLeft;
    QuadTreeNode* bottomRight;

    glm::vec2 TLCoord;
    glm::vec2 BRCoord;

    std::vector<Box*> boxes;

    void init() {
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    bool isLeaf() {
        return (!topLeft && !topRight && !bottomRight && !bottomLeft);
    }

    void insertBox(Box* box) {

    }
};

