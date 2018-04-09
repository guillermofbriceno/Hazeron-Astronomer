#pragma once

#include "StarMap.h"

void startCli(StarMap& map);
void help(const std::string& commmand);
void findRingworld(StarMap &map);
void detail(const std::vector<Resource>& memory, const std::string& selection);
void findBestResource(std::vector<Resource> &memory, std::string resource, StarMap &map);
void findAllBest(std::vector<Resource> &memory, StarMap &map);

std::vector<std::vector<std::string>> 
generateResourceTable(int currentMemory, const std::vector<std::string>& parameters, 
		const std::vector<Resource>& bestResults, const StarMap& map);
void displayTable(std::vector<std::vector<std::string>> dispText, int separation);
bool isDigit(std::string s);
