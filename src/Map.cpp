#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/Map.hpp"
#include "../include/Engine.hpp"

Map::Map(int idMap) {
    boxes = new QuadTreeNode();
    loadMapInfo(idMap);
}

void Map::update() {
    boxes->updateBoxes();

    handleSwitchesCollisions();
    handleZones();

    if (isNear(currentPlayer)) {
        currentPlayer->setStatus(true);
        if (!isMapDone()) {
            chooseNextPlayer();
        } else {
            done = true;
        }
    }

    for (size_t i = 0; i < players.size(); i++) {
        glm::vec2 largerTL = {players[i]->getTLPosition().x - 1, players[i]->getTLPosition().y + 1};
        glm::vec2 largerBR = {players[i]->getBRPosition().x + 1, players[i]->getBRPosition().y - 1};

        // We give a largerTL and BR to the player to avoid collisions issues implying the QuadTree and ends of Nodes
        players[i]->setBoxes(boxes->findCorrespondingBoxes(largerTL, largerBR));
        players[i]->setPlayers(players);
        players[i]->removeCurrentFromArray(i);
        players[i]->posUpdate();

        if (getCurrentPlayer() != players[i]) {
            players[i]->setInactive();
        }
    }
}

void Map::handleSwitchesCollisions() const {
    for (auto &sw1tch: switches) {
        bool isActivated = false;
        for (auto player: players) {
            glm::vec2 playerBL = player->getBLPosition();
            float width = player->getWidth();

            // Collisions with a switch
            if (((isContained(sw1tch->getX() - 0.2f, playerBL.x, playerBL.x + width)
                  || isContained(sw1tch->getX() + 0.2f, playerBL.x, playerBL.x + width))
                 && isContained(sw1tch->getY() + 0.2f, playerBL.y, playerBL.y + 0.3f))) {
                isActivated = true;
            }
        }

        if (isActivated)
            sw1tch->activate();
        else
            sw1tch->deactivate();
    }
}

/**
 * @brief Get if a player is near to his end position
 * @param player
 * @return
 */
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
    for (auto zone: zones) {
        zone->draw();
    }

    for (auto &sw1tch: switches) {
        sw1tch->draw();
        sw1tch->drawZones();
    }

    for (auto &player: players) {
        player->draw();
        player->drawEndPlace();
    }
    currentPlayer->drawGhost();

    drawBlocks();
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

Zone *Map::getCurrentZone(std::vector<Zone *> givenZones) {
    Zone *currentZone = nullptr;

    for (auto &zone: givenZones) {
        glm::vec2 playerBL = currentPlayer->getBLPosition();
        glm::vec2 playerBR = currentPlayer->getBRPosition();
        playerBL.y += 0.1;
        playerBR.y += 0.1;
        if (zone->contains(playerBL, playerBR)) {
            currentZone = zone;
            break;
        }
    }
    return currentZone;
}

Zone *Map::getCurrentZoneFromSwitches() {
    Zone *currentZone = nullptr;
    for (auto &sw1tch: switches) {
        if (sw1tch->isActive() && getCurrentZone(sw1tch->getZones()) != nullptr) {
            currentZone = getCurrentZone(sw1tch->getZones());
        }
    }
    return currentZone;
}

/**
 * @brief Handle the players changes if he's in a zone (switch or basic zone)
 */
void Map::handleZones() {
    Zone *currentZone = getCurrentZone(zones);
    if (getCurrentZoneFromSwitches()) {
        currentZone = getCurrentZoneFromSwitches();
    }

    if (currentZone)
        currentZone->applyChanges(currentPlayer);
    else {
        if (currentPlayer->getCurrentChanges() == Changes::Mini)
            currentPlayer->unsetMiniMode();
        else if (currentPlayer->getCurrentChanges() == Changes::Maxi)
            currentPlayer->unsetMaxiMode();
        currentPlayer->unsetSuperJumpMode();
        currentPlayer->unsetWarpedGravity();
    }

    drawBlocks();
}

void Map::drawBlocks() {
    // Draw everything when the camera is zooming at the beginning
    if (drawEverything) {
        boxes->drawBoxes();
        return;
    }

    glm::vec2 center = currentPlayer->getCenteredPosition();

    glm::vec2 TLScreen = glm::vec2(
            1 + center.x + (float) (-mapZoom),
            center.y + (float) (mapZoom) * (1 - Engine::PLAYER_Y_AXIS)
    );

    glm::vec2 BRScreen = glm::vec2(
            center.x + (float) (mapZoom) - 1,
            center.y + (float) (-mapZoom) * Engine::PLAYER_Y_AXIS
    );

    boxes->drawCorrespondingQuadForScreen(
            TLScreen,
            BRScreen
    );
}

