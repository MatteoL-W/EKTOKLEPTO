#pragma once

#include <vector>
#include <iostream>
#include "../Box.hpp"
#include "../tools/utils.hpp"
#include "../tools/draw.hpp"

const int MAX_RECURSIVE_HEIGHT = 3;

struct QuadTreeNode {
    QuadTreeNode *topLeft;
    QuadTreeNode *topRight;
    QuadTreeNode *bottomLeft;
    QuadTreeNode *bottomRight;

    glm::vec2 TLQuad;
    glm::vec2 BRQuad;
    glm::vec2 centerQuad;

    std::vector<Box *> boxes;

    void init(glm::vec2 TLPosition, glm::vec2 BRPosition);

    bool isLeaf() const;

    void drawCorrespondingQuadForScreen(glm::vec2 TLPosition, glm::vec2 BRPosition);

    std::vector<Box*> findCorrespondingBoxes(glm::vec2 playerPosition);

    void drawBoxes(bool drawQuad = false);

    void insertBox(Box *box, int count = 0);

    void initNodes();

    void insertAtTheRightPlace(Box *box, int count) const;

    void updateBoxes();
};

