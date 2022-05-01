#pragma once

#include <iostream>
#include <vector>
#include "Box.hpp"
#include "Player.hpp"
#include "tools/QuadTreeNode.hpp"

const int MAX_SQUARES = 32;
const int MAX_PLAYERS = 5;

class Map {
public:
    Map();

    ~Map() = default;

    void update();

    void draw();

    size_t boxCount = 0;

    size_t playerCount = 0;

    int currentPlayerId = 0;

    void setCurrentPlayer(int i);

    int getMapWidth() const { return mapWidth; };
    int getMapHeight() const { return mapHeight; };

    std::vector<Player *> getPlayers() { return players; };

    Player* getCurrentPlayer() { return currentPlayer; };

    QuadTreeNode* getBoxes() { return boxes; };

    void chooseNextPlayer();

private:
    void loadMapInfo(int idMap);

    void stockMapInfo(std::string mapInformation[3][MAX_SQUARES]);

    void stockPlayers(std::string *);

    void stockBoxes(std::string *);

    int mapWidth, mapHeight;

    QuadTreeNode *boxes;

    std::vector<Player *> players;

    Player *currentPlayer;
};
