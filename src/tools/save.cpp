#include "../include/tools/save.hpp"

/**
 * @brief Get the amount of saved game
 * @return
 */
int getSlotUsedAmount() {
    std::string savedLevel;
    std::ifstream savedFile(Game::saveEmplacements);
    int counter = 0;

    if (savedFile.is_open()) {
        std::string currentLine;

        while (getline(savedFile, currentLine)) {
            if (currentLine.empty()) {
                counter++;
            }
        }
        savedFile.close();
    }
    return counter;
}

/**
 * @brief Return the level of a save
 * @param saveId
 * @return
 */
std::string readSave(int saveId) {
    std::string savedLevel;
    std::ifstream savedFile(Game::saveEmplacements);
    std::string saveInformation[5][MAX_LEVELS];
    int partCounting = -1, counter = 0;

    if (savedFile.is_open()) {
        std::string currentLine;

        while (getline(savedFile, currentLine)) {
            if (currentLine.empty()) {
                if (partCounting == saveId) {
                    return saveInformation[partCounting][counter - 1];
                }
                partCounting++;
                counter = 0;
                continue;
            }
            saveInformation[partCounting][counter] = currentLine;

            counter++;
        }

        if (partCounting == saveId) {
            return saveInformation[partCounting][counter - 1];
        }

        savedFile.close();
    }
    return "";
}

/**
 * @brief Save in the save file the current level.
 * @param saveContent
 */
void save(const std::string &saveContent) {
    std::ofstream saveFile(Game::saveEmplacements, std::ios::app);
    if (saveFile.is_open()) {
        saveFile << "\n" << saveContent << "\n";
        saveFile.close();
    } else std::cout << "Unable to open file - save";
}

void eraseSaves() {
    std::ofstream saveFile(Game::saveEmplacements);
    if (saveFile.is_open()) {
        saveFile << "";
        saveFile.close();
    } else std::cout << "Unable to open file - eraseSaves";
}
