#pragma once

#include <vector>
#include "../Box.hpp"
#include "../tools/utils.hpp"


struct QuadTreeNode {
    QuadTreeNode* topLeft;
    QuadTreeNode* topRight;
    QuadTreeNode* bottomLeft;
    QuadTreeNode* bottomRight;

    glm::vec2 TLQuad;
    glm::vec2 BRQuad;
    glm::vec2 centerQuad;

    std::vector<Box*> boxes;

    void init(glm::vec2 TLPosition, glm::vec2 BRPosition) {
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;

        TLQuad = TLPosition;
        BRQuad = BRPosition;
        centerQuad = getPositionCenter(TLPosition, BRPosition);
    }

    bool isLeaf() {
        return (!topLeft && !topRight && !bottomRight && !bottomLeft);
    }

    void insertBox(Box* box) {
        // Si c'est une leaf
        // On ajoute la box dans le vecteur de box associé
        if (isLeaf() && boxes.size() < 4) {
            boxes.push_back(box);
            return;
        }

        // Si c'est pas une leaf
        // On boucle sur les coins et on check ils sont dans quels zones
        // On envoie la box dans les zones touchées
        if (isLeaf() && boxes.size() > 4) {
            for (size_t i = 0; i < boxes.size(); i++) {
                bool left = false;
                bool top = false;

                // Là j'ai une box : boxes[i]
                // Je mets la box dans l'enfant(s) qui correspond
                if (boxes[i]->getTLPosition().x < centerQuad.x) {
                    // une partie est à gauche
                    left = true;
                }

                if (boxes[i]->getTRPosition().x > centerQuad.x) {
                    // une partie est à droite
                    left = false;
                }

                if (boxes[i]->getBRPosition().y < centerQuad.y) {
                    // une partie est en dessous
                    top = false;
                }

                if (boxes[i]->getTLPosition().y > centerQuad.y) {
                    // une partie est au dessus
                    top = true;
                }

                if (top && left) {
                    if (!topLeft)
                        topLeft->init(TLQuad, centerQuad);
                    topLeft->insertBox(boxes[i]);
                } else if (top) {
                    if (!topRight)
                        topRight->init(glm::vec2(centerQuad.x, TLQuad.y), glm::vec2(BRQuad.x, centerQuad.y));
                    topRight->insertBox(boxes[i]);
                } else if (left) {
                    if (!bottomLeft)
                        bottomLeft->init(glm::vec2(TLQuad.x, centerQuad.y), glm::vec2(centerQuad.x, BRQuad.y));
                    bottomLeft->insertBox(boxes[i]);
                } else {
                    if (!bottomRight)
                        bottomRight->init(centerQuad, BRQuad);
                    bottomRight->insertBox(boxes[i]);
                }
            }
        }

        if (!isLeaf()) {
            bool left = false;
            bool top = false;

            // Là j'ai une box : boxes[i]
            // Je mets la box dans l'enfant(s) qui correspond
            if (box->getTLPosition().x < centerQuad.x) {
                // une partie est à gauche
                left = true;
            }

            if (box->getTRPosition().x > centerQuad.x) {
                // une partie est à droite
                left = false;
            }

            if (box->getBRPosition().y < centerQuad.y) {
                // une partie est en dessous
                top = false;
            }

            if (box->getTLPosition().y > centerQuad.y) {
                // une partie est au dessus
                top = true;
            }

            if (top && left) {
                topLeft->insertBox(box);
            } else if (top) {
                topRight->insertBox(box);
            } else if (left) {
                bottomLeft->insertBox(box);
            } else {
                bottomRight->insertBox(box);
            }
        }
    }
};

