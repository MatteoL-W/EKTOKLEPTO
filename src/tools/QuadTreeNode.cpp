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

/**
 * @brief Draw the content of the screen (optimize render)
 * @param TLPosition
 * @param BRPosition
 */
void QuadTreeNode::drawCorrespondingQuadForScreen(glm::vec2 TLPosition, glm::vec2 BRPosition) {
    if (isLeaf()) {
        for (auto &box: boxes) {
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

/**
 * @brief Find the quad containing a vec2 position (used to find collisions around the player)
 * @param playerPosition
 * @return
 */
std::vector<Box*> QuadTreeNode::findCorrespondingBoxes(glm::vec2 playerPosition) {
    if (isLeaf())
        return this->boxes;

    if (!isLeaf()) {
        bool top = playerPosition.y > centerQuad.y;
        bool right = playerPosition.x > centerQuad.x;

        if (top) {
            if (right)
               return topRight->findCorrespondingBoxes(playerPosition);
            else
                return topLeft->findCorrespondingBoxes(playerPosition);
        } else {
            if (right)
                return bottomRight->findCorrespondingBoxes(playerPosition);
            else
                return bottomLeft->findCorrespondingBoxes(playerPosition);
        }
    }

    return (new QuadTreeNode())->boxes;
}

/**
 * @brief [DEPRECATED] Draw a box and its content
 * @param drawQuad
 */
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

/**
 * @brief Insert a box into a quadtree
 * @param box
 */
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

/**
 * @brief Function used to locate in which quad should be a box located
 * @param box
 */
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

void QuadTreeNode::updateBoxes() {
    if (isLeaf()) {
        for (auto &box: boxes) {
            if (box->isMovable())
                box->update();
        }
        return;
    }

    // When it's not a leaf, nodes are defined, so we assume we have no verification.
    topLeft->updateBoxes();
    topRight->updateBoxes();
    bottomLeft->updateBoxes();
    bottomRight->updateBoxes();
}
