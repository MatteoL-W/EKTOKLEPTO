#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/Map.hpp"
#include "../include/Box.hpp"
#include "../include/tools/QuadTreeNode.hpp"

Map::Map() {
    //loadMapInfo(1);
    root = new QuadTreeNode();
    root->init(glm::vec2(0, 20), glm::vec2(20, 0));

    //topleft
    root->insertBox(new Box(1, 19, 2, 18));
    root->insertBox(new Box(1, 17, 2, 16));
    root->insertBox(new Box(1, 15, 2, 14));
    root->insertBox(new Box(1, 13, 2, 12));
    root->insertBox(new Box(1, 11, 2, 10));

    root->insertBox(new Box(3, 19, 4, 18));
    root->insertBox(new Box(3, 17, 4, 16));
    root->insertBox(new Box(3, 15, 4, 14));
    root->insertBox(new Box(3, 13, 4, 12));
    root->insertBox(new Box(3, 11, 4, 10));

    //bottomleft
    root->insertBox(new Box(3, 4, 5, 2));

    //top right
    root->insertBox(new Box(12, 17, 14, 15));

    // bottom right
    root->insertBox(new Box(12, 2, 14, 0));
    root->insertBox(new Box(12, 4, 14, 6));

    QuadTreeNode* myArea = root->findCorrespondingQuad(glm::vec2(1,19));

}

void Map::update() {
}

void Map::draw() {
    root->drawBoxes(true);

    /*for (size_t i = 0; i < boxCount; i++) {
        boxes[i]->draw();
    }

    for (size_t i = 0; i < playerCount; i++) {
        players[i]->draw();
        players[i]->drawEndPlace();
    }*/
}

/**
 * @brief Saving the data from .txt into the object properties
 * @param idMap
 */
void Map::loadMapInfo(int idMap) {
    int partCounting = 0, counter = 0;

    std::string mapPath = "assets/maps/" + std::to_string(idMap) + ".txt";
    std::string mapInformation[3][MAX_SQUARES];
    std::fstream mapFile;

    mapFile.open(mapPath, std::ios::in); //open a file to perform read operation using file object
    if (mapFile.is_open()) {   //checking whether the file is open
        std::string currentLine;

        while (getline(mapFile, currentLine)) {  //read data from file object and put it into string.
            if (currentLine.empty()) {
                partCounting++;
                counter = 0;
                continue;
            }
            mapInformation[partCounting][counter] = currentLine;
            counter++;
        }
        mapFile.close();   //close the file object.
    }

    stockMapInfo(mapInformation);
}

void Map::stockMapInfo(std::string (*mapInformation)[MAX_SQUARES]) {
    // Stock width an height in the object data
    char *widthAndHeight = mapInformation[0][0].data();
    mapWidth = atoi(strtok(widthAndHeight, " "));
    mapHeight = atoi(strtok(nullptr, " "));

    stockPlayers(mapInformation[1]);
    stockBoxes(mapInformation[2]);
}

/**
 * @brief Load all the boxes from txt file in the boxes vector
 * @param lineInformation
 */
void Map::stockBoxes(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_SQUARES; i++) {
        char *rectanglesInformation = lineInformation[i].data();
        float parameter[4] = {0, 0, 0, 0};
        int counter = 0;

        char *line = strtok(rectanglesInformation, " ");
        while (line != NULL) {
            parameter[counter] = atoi(line);
            line = strtok(NULL, " ");
            counter++;
        }

        if (parameter[0] != parameter[1] || parameter[0] != parameter[2] || parameter[0] != parameter[3]) {
            boxes.push_back(new Box(parameter[0], parameter[1], parameter[2], parameter[3]));
            boxCount++;
        }
    }
}

/**
 * @brief Load all the players from the txt in the players vector
 * @param lineInformation
 */
void Map::stockPlayers(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        char *playersInformation = lineInformation[i].data();
        float parameter[5] = {0, 0, 0, 0, 0};
        int counter = 0;

        char *line = strtok(playersInformation, " ");
        while (line != NULL) {
            parameter[counter] = atoi(line);
            line = strtok(NULL, " ");
            counter++;
        }

        if (parameter[0] != parameter[1] || parameter[0] != parameter[2] || parameter[0] != parameter[3] ||
            parameter[0] != parameter[4]) {
            players.push_back(new Player(parameter[0], parameter[1], parameter[2], parameter[3], parameter[4]));
            playerCount++;
        }
    }

    if (players[0] != nullptr) {
        setCurrentPlayer(currentPlayerId);
    }
}

void Map::setCurrentPlayer(int i) {
    currentPlayer = players[i];
    currentPlayerId = i;
}

