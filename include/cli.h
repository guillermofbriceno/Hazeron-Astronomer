#pragma once

#include "StarMap.h"

void startCli(StarMap &map);
void help(std::string commmand);
void findRingworld(StarMap &map);
void findBestResource(std::string resource, StarMap &map);
void findAllBest(StarMap &map);
std::vector<std::vector<std::string>> generateResourceTable(std::vector<std::string>
    parameters, std::vector<Resource> bestResults, StarMap &map);
void displayTable(std::vector<std::vector<std::string>> dispText, int separation);
