#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/Map.hpp"

Map::Map(int idMap) {
    boxes = new QuadTreeNode();
    loadMapInfo(idMap);
}

void Map::update() {
    //if (!isNear(currentPlayer)) {}
    currentPlayer->moveRight();

    boxes->updateBoxes();
    updateZone();

    if (isNear(currentPlayer)) {
        currentPlayer->setStatus(true);
        if (!isMapDone()) {
            chooseNextPlayer();
        } else {
            done = true;
        }
    }
}

bool Map::isNear(Player *const &player) {
    float margin = 0.2;

    if ((player->getCenteredPositionEnd().x - margin < player->getCenteredPosition().x &&
         player->getCenteredPosition().x < player->getCenteredPositionEnd().x + margin)
        && (player->getCenteredPositionEnd().y - margin < player->getCenteredPosition().y &&
            player->getCenteredPosition().y < player->getCenteredPositionEnd().y + margin)) {
        return true;
    }
    return false;
}

void Map::draw() {
    for (size_t i = 0; i < zones.size(); i++) {
        zones[i]->draw();
    }

    for (size_t i = 0; i < playerCount; i++) {
        players[i]->draw();
        players[i]->drawEndPlace();
    }

    for (size_t i = 0; i < switches.size(); i++) {
        switches[i]->draw();
    }
}

/**
 * @brief Saving the data from .txt into the object properties
 * @param idMap
 */
void Map::loadMapInfo(int idMap) {
    int partCounting = 0, counter = 0;

    std::string mapPath = "assets/maps/" + std::to_string(idMap) + ".txt";
    std::string mapInformation[5][MAX_SQUARES];
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
    mapWidth = atof(strtok(widthAndHeight, " "));
    mapHeight = atof(strtok(nullptr, " "));
    mapZoom = atof(strtok(nullptr, " "));

    boxes->init(glm::vec2(0, mapHeight), glm::vec2(mapWidth, 0));

    stockPlayers(mapInformation[1]);
    stockBoxes(mapInformation[2]);
    stockZones(mapInformation[4]);
    stockSwitches(mapInformation[3]);

}

/**
 * @brief Load all the boxes from txt file in the boxes vector
 * @param lineInformation
 */
void Map::stockBoxes(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_SQUARES; i++) {
        char *rectanglesInformation = lineInformation[i].data();
        float parameter[7] = {0, 0, 0, 0, 0, 0, 0};
        int counter = 0;

        char *line = strtok(rectanglesInformation, " ");
        while (line != NULL) {
            parameter[counter] = atof(line);
            line = strtok(NULL, " ");
            counter++;
        }

        if (parameter[0] != parameter[1] || parameter[0] != parameter[2] || parameter[0] != parameter[3]) {
            boxes->insertBox(new Box(parameter[0], parameter[1], parameter[2], parameter[3], parameter[4], parameter[5],
                                     parameter[6]));
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

void Map::stockSwitches(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_SWITCHES; i++) {
        char *switchesInformation = lineInformation[i].data();
        float parameter[4] = {0, 0, 0, 0};
        int counter = 0;

        char *line = strtok(switchesInformation, " ");
        while (line != NULL) {
            parameter[counter] = atoi(line);
            line = strtok(NULL, " ");
            counter++;
        }

        if (parameter[0] != parameter[1] || parameter[0] != parameter[2] || parameter[0] != parameter[3]) {
            auto *newSwitch = new Switch((int) parameter[0], (int) parameter[1], parameter[2], parameter[3]);
            newSwitch->linksToZones(zones);
            switches.push_back(newSwitch);
        }
    }
}

/**
 * @brief Load all the zones from the txt in the zones vector
 * @param lineInformation
 */
void Map::stockZones(std::string lineInformation[32]) {
    for (int i = 0; i < MAX_SWITCHES; i++) {
        char *zonesInformation = lineInformation[i].data();
        float parameter[6] = {0, 0, 0, 0, 0, 0};
        int counter = 0;

        char *line = strtok(zonesInformation, " ");
        while (line != NULL) {
            parameter[counter] = atoi(line);
            line = strtok(NULL, " ");
            counter++;
        }

        if (parameter[0] != parameter[1] || parameter[0] != parameter[2] || parameter[0] != parameter[3] ||
            parameter[0] != parameter[4]) {
            auto *newZone = new Zone((int) parameter[0], parameter[1], parameter[2], parameter[3], parameter[4],
                                     (int) parameter[5]);
            zones.push_back(newZone);
        }
    }
}

void Map::setCurrentPlayer(size_t i) {
    currentPlayer = players[i];
    currentPlayerId = i;
}

void Map::chooseNextPlayer() {
    size_t idNextPlayer = (currentPlayerId + 1 < playerCount) ? currentPlayerId + 1 : 0;
    setCurrentPlayer(idNextPlayer);
}

bool Map::isMapDone() {
    bool finished = true;
    for (auto &player: players) {
        if (!isNear(player)) {
            finished = false;
        }
    }
    return finished;
}

void Map::restart() {
    for (auto &player: players) {
        player->reset();
    }
}

void Map::updateZone() {
    Zone* currentZone = nullptr;
    for (auto &zone: zones) {
        if (zone->contains(currentPlayer->getBLPosition())) {
            currentZone = zone;
            break;
        }
    }

    if (currentZone)
        currentZone->applyChanges(currentPlayer);
    else if (currentPlayer->getWidth() != currentPlayer->getFixWidth() || currentPlayer->getHeight() != currentPlayer->getFixHeight())
        currentPlayer->unsetMiniMode();
}