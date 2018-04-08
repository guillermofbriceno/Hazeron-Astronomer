#pragma once

#include "StarMap.h"

void startCli(StarMap &map);
void help(std::string commmand);
void findRingworld(StarMap &map);
void detail(const std::vector<Resource>& memory, const std::string& selection);
void findBestResource(std::vector<Resource> &memory, std::string resource, StarMap &map);
void findAllBest(std::vector<Resource> &memory, StarMap &map);
std::vector<std::vector<std::string>> generateResourceTable(int currentMemory, std::vector<std::string>
    parameters, std::vector<Resource> bestResults, StarMap &map);
void displayTable(std::vector<std::vector<std::string>> dispText, int separation);
bool isDigit(std::string s);
