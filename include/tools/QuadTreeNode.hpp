#pragma once

#include <vector>
#include <iostream>
#include "../Box.hpp"
#include "../tools/utils.hpp"
#include "../tools/draw.hpp"


struct QuadTreeNode {
    QuadTreeNode *topLeft;
    QuadTreeNode *topRight;
    QuadTreeNode *bottomLeft;
    QuadTreeNode *bottomRight;

    glm::vec2 TLQuad;
    glm::vec2 BRQuad;
    glm::vec2 centerQuad;

    std::vector<Box *> boxes;

    void init(glm::vec2 TLPosition, glm::vec2 BRPosition) {
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;

        TLQuad = TLPosition;
        BRQuad = BRPosition;
        centerQuad = getPositionCenter(TLPosition, BRPosition);
    }

    void drawBoxes() {
        if (isLeaf()) {
            // red square
            glColor3f(1, 0, 0);
            drawRect(TLQuad, BRQuad, false);

            for (auto & box : boxes) {
                box->draw();
            }
            return;
        }

        if (topLeft) {
            topLeft->drawBoxes();
        }

        if (topRight) {
            topRight->drawBoxes();
        }

        if (bottomLeft) {
            bottomLeft->drawBoxes();
        }

        if (bottomRight) {
            bottomRight->drawBoxes();
        }

        return;
    }

    bool isLeaf() const {
        return (!topLeft && !topRight && !bottomRight && !bottomLeft);
    }

    void insertBox(Box *box) {
        if (isLeaf()) { // si topright; topleft; bottomright et bottomleft sont nullptr
            boxes.push_back(box);
        }

        if (isLeaf() && boxes.size() > 3) {
            // Initialization
            if (!topRight) {
                topRight = new QuadTreeNode();
                topRight->init(glm::vec2(centerQuad.x, TLQuad.y), glm::vec2(BRQuad.x, centerQuad.y));
            }

            if (!topLeft) {
                topLeft = new QuadTreeNode();
                topLeft->init(TLQuad, centerQuad);
            }

            if (!bottomLeft) {
                bottomLeft = new QuadTreeNode();
                bottomLeft->init(glm::vec2(TLQuad.x, centerQuad.y), glm::vec2(centerQuad.x, BRQuad.y));
            }

            if (!bottomRight) {
                bottomRight = new QuadTreeNode();
                bottomRight->init(centerQuad, BRQuad);
            }

            // Loop on all the boxes already here
            for (auto & currentBox : boxes) {
                insertAtTheRightPlace(currentBox);
            }
            boxes.clear();
            return;
        }

        if (!isLeaf()) {
            insertAtTheRightPlace(box);
        }
    }

    void insertAtTheRightPlace(Box* box) const {
        bool left = box->getTLPosition().x < centerQuad.x;
        bool right = box->getTRPosition().x > centerQuad.x;
        bool bottom = box->getBRPosition().y < centerQuad.y;
        bool top = box->getTLPosition().y > centerQuad.y;

        if (top) {
            if (left)
                topLeft->insertBox(box);
            if (right)
                topRight->insertBox(box);
        }

        if (bottom) {
            if (left)
                bottomLeft->insertBox(box);
            if (right)
                bottomRight->insertBox(box);
        }
    }
};

