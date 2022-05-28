#include <iostream>
#include <fstream>
#include "../Game.hpp"

const int MAX_LEVELS = 7;

int getSlotUsedAmount();
std::string readSave(int saveId);
void save(const std::string& saveContent);
void eraseSaves();
