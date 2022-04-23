#include <fstream>
#include <GL/gl.h>
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
    for (int i = 0; i < boxCount; i++) {
        boxes[i]->draw();
    }
}

void Map::loadMapInfo(int idMap) {
    int partCounting = 0, counter = 0;
    std::fstream mapFile;
    std::string mapInformation[3][MAX_SQUARES];
    std::string mapPath = "assets/maps/" + std::to_string(idMap) + ".txt";

    mapFile.open(mapPath, std::ios::in); //open a file to perform read operation using file object
    if (mapFile.is_open()){   //checking whether the file is open
        std::string currentLine;

        while(getline(mapFile, currentLine)){  //read data from file object and put it into string.
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
    char* widthAndHeight = mapInformation[0][0].data();
    mapWidth = atoi(strtok(widthAndHeight, " "));
    mapHeight = atoi(strtok(nullptr, " "));

    // créer les players


    // stocker dans tableaux
    for (int i = 0; i < MAX_SQUARES; i++) {
        char* rectanglesInformation = mapInformation[2][i].data();
        int counter = 0;
        int parameter[4] = {0, 0, 0, 0};

        char* line = strtok(rectanglesInformation, " ");
        while (line != NULL) {
            parameter[counter] = atoi(line);
            line = strtok(NULL, " ");
            counter++;
        }

        if (parameter[0] != parameter[1] || parameter[0] != parameter[2] || parameter[0] != parameter[3]) {
            //std::cout << "Box n" << i << " : " << parameter[0] << " " << parameter[1] << " " << parameter[2] << " " << parameter[3] << std::endl;
            boxes[boxCount] = new Box(parameter[0], parameter[1], parameter[2], parameter[3]);
            boxCount++;
        }
    }
}

