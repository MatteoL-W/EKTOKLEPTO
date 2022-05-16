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
    explicit Map(int idMap);

    ~Map() = default;

    void update();

    void draw();

    void chooseNextPlayer();

    void restart();

    size_t boxCount = 0;

    size_t playerCount = 0;

    size_t currentPlayerId = 0;

    void setCurrentPlayer(size_t i);

    int getMapWidth() const { return mapWidth; };

    int getMapHeight() const { return mapHeight; };

    int getMapZoom() const { return mapZoom; };

    std::vector<Player *> getPlayers() { return players; };

    Player *getCurrentPlayer() { return currentPlayer; };

    QuadTreeNode *getBoxes() { return boxes; };

    bool isFinished() const { return done; };

private:
    static bool isNear(Player *const &player);

    bool isMapDone();

    void loadMapInfo(int idMap);

    void stockMapInfo(std::string mapInformation[3][MAX_SQUARES]);

    void stockPlayers(std::string *);

    void stockBoxes(std::string *);

    int mapWidth, mapHeight, mapZoom;

    QuadTreeNode *boxes;

    std::vector<Player *> players;

    Player *currentPlayer;

    bool done = false;

    void drawBlocks();
};
