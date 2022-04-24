#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/Map.hpp"

Map::Map() {
    loadMapInfo(1);
}

/**
 * @brief Update the map
 */
void Map::update() {
}

/**
 * @brief Draw the map
 */
void Map::draw() {
    for (size_t i = 0; i < boxCount; i++) {
        boxes[i]->draw();
    }

    for (size_t i = 0; i < playerCount; i++) {
        players[i]->draw();
        players[i]->drawEndPlace();
    }
}

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
    char *widthAndHeight = mapInformation[0][0].data();
    mapWidth = atoi(strtok(widthAndHeight, " "));
    mapHeight = atoi(strtok(nullptr, " "));

    stockPlayers(mapInformation[1]);
    stockBoxes(mapInformation[2]);
}

void Map::stockBoxes(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_SQUARES; i++) {
        char *rectanglesInformation = lineInformation[i].data();
        int counter = 0;
        float parameter[4] = {0, 0, 0, 0};

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

void Map::stockPlayers(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        char *playersInformation = lineInformation[i].data();
        int counter = 0;
        float parameter[5] = {0, 0, 0, 0, 0};

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
}

