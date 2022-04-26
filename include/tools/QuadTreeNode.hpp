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

    void draw() const {
        glColor3f(1, 0, 0);
        drawRect(TLQuad, BRQuad, false);

        for (size_t i = 0; i < boxes.size(); i++) {
            boxes[i]->draw();
        }
    }

    bool isLeaf() const {
        return (!topLeft && !topRight && !bottomRight && !bottomLeft);
    }

    void insertBox(Box *box) {
        // Si c'est une leaf
        // On ajoute la box dans le vecteur de box associé
        if (isLeaf()) {
            boxes.push_back(box);
        }

        // Si c'est pas une leaf
        // On boucle sur les coins et on check ils sont dans quels zones
        // On envoie la box dans les zones touchées
        if (isLeaf() && boxes.size() > 3) {
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
            for (size_t i = 0; i < boxes.size(); i++) {
                bool left = false;
                bool right = false;
                bool bottom = false;
                bool top = false;

                // Là j'ai une box : boxes[i]
                // Je mets la box dans l'enfant(s) qui correspond
                if (boxes[i]->getTLPosition().x < centerQuad.x) {
                    // une partie est à gauche
                    left = true;
                }

                if (boxes[i]->getTRPosition().x > centerQuad.x) {
                    // une partie est à droite
                    right = true;
                }

                if (boxes[i]->getBRPosition().y < centerQuad.y) {
                    // une partie est en dessous
                    bottom = true;
                }

                if (boxes[i]->getTLPosition().y > centerQuad.y) {
                    // une partie est au dessus
                    top = true;
                }

                // Vérification et insert
                if (top && left) {
                    topLeft->insertBox(boxes[i]);
                }

                if (top && right) {
                    topRight->insertBox(boxes[i]);
                }

                if (bottom && left) {
                    bottomLeft->insertBox(boxes[i]);
                }

                if (bottom && right) {
                    bottomRight->insertBox(boxes[i]);
                }
            }
            boxes.clear();
        }

        if (!isLeaf()) {
            bool left = false;
            bool right = false;
            bool bottom = false;
            bool top = false;

            // Là j'ai une box : boxes[i]
            // Je mets la box dans l'enfant(s) qui correspond
            if (box->getTLPosition().x < centerQuad.x) {
                // une partie est à gauche
                left = true;
            }

            if (box->getTRPosition().x > centerQuad.x) {
                // une partie est à droite
                right = true;
            }

            if (box->getBRPosition().y < centerQuad.y) {
                // une partie est en dessous
                bottom = true;
            }

            if (box->getTLPosition().y > centerQuad.y) {
                // une partie est au dessus
                top = true;
            }

            if (top && left) {
                topLeft->insertBox(box);
            }

            if (top && right) {
                topRight->insertBox(box);
            }

            if (bottom && left) {
                bottomLeft->insertBox(box);
            }

            if (bottom && right) {
                bottomRight->insertBox(box);
            }
        }
    }
};

