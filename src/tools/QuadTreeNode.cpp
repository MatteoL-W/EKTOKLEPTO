#include "../../include/tools/QuadTreeNode.hpp"

void QuadTreeNode::init(glm::vec2 TLPosition, glm::vec2 BRPosition) {
    topLeft = nullptr;
    topRight = nullptr;
    bottomLeft = nullptr;
    bottomRight = nullptr;

    TLQuad = TLPosition;
    BRQuad = BRPosition;
    centerQuad = getPositionCenter(TLPosition, BRPosition);
}

bool QuadTreeNode::isLeaf() const {
    return (!topLeft && !topRight && !bottomRight && !bottomLeft);
}

void QuadTreeNode::drawCorrespondingQuadForScreen(glm::vec2 TLPosition, glm::vec2 BRPosition) {
    if (isLeaf()) {
        for (auto &box: boxes) {
            glColor3f(1, 0, 0);
            drawRect(TLQuad, BRQuad, false);
            box->draw();
        }
    }

    if (!isLeaf()) {
        bool left = TLPosition.x < centerQuad.x;
        bool right = BRPosition.x > centerQuad.x;
        bool bottom = BRPosition.y < centerQuad.y;
        bool top = TLPosition.y > centerQuad.y;

        if (left && top)
            topLeft->drawCorrespondingQuadForScreen(TLPosition, BRPosition);

        if (right && top)
            topRight->drawCorrespondingQuadForScreen(TLPosition, BRPosition);

        if (left && bottom)
            bottomLeft->drawCorrespondingQuadForScreen(TLPosition, BRPosition);

        if (right && bottom)
            bottomRight->drawCorrespondingQuadForScreen(TLPosition, BRPosition);
    }
}

QuadTreeNode *QuadTreeNode::findCorrespondingQuad(glm::vec2 playerPosition) {
    if (isLeaf())
        return this;

    if (!isLeaf()) {
        bool top = playerPosition.y > centerQuad.y;
        bool right = playerPosition.x > centerQuad.x;

        if (top) {
            if (right)
                topRight->findCorrespondingQuad(playerPosition);
            else
                topLeft->findCorrespondingQuad(playerPosition);
        } else {
            if (right)
                bottomRight->findCorrespondingQuad(playerPosition);
            else
                bottomLeft->findCorrespondingQuad(playerPosition);
        }
    }
}

void QuadTreeNode::drawBoxes(bool drawQuad) {
    if (isLeaf()) {
        if (drawQuad) {
            glColor3f(1, 0, 0);
            drawRect(TLQuad, BRQuad, false);
        }

        for (auto &box: boxes) {
            box->draw();
        }
        return;
    }

    // When it's not a leaf, nodes are defined, so we assume we have no verification.
    topLeft->drawBoxes(drawQuad);
    topRight->drawBoxes(drawQuad);
    bottomLeft->drawBoxes(drawQuad);
    bottomRight->drawBoxes(drawQuad);
}

void QuadTreeNode::insertBox(Box *box) {
    if (isLeaf()) {
        boxes.push_back(box);
    }

    if (isLeaf() && boxes.size() > 3) {
        // Initialization
        initNodes();

        // Loop on all the boxes already here
        for (auto &currentBox: boxes) {
            insertAtTheRightPlace(currentBox);
        }
        boxes.clear();
        return;
    }

    if (!isLeaf()) {
        insertAtTheRightPlace(box);
    }
}

void QuadTreeNode::initNodes() {
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
}

void QuadTreeNode::insertAtTheRightPlace(Box *box) const {
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

