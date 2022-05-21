#include <iostream>
#include <fstream>
#include "../Game.hpp"

const int MAX_LEVELS = 3;

std::string readSave(int saveId);
void save(const std::string& saveContent);
