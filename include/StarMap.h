#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "elements.h"

class StarMap {
private:
  std::vector<galaxy> galaxyVec;
  std::vector<sector> sectorVec;
  std::vector<sys> sysVec;
  std::vector<star> starVec;
  std::vector<planet> planetVec;
  std::vector<Resource> resourceVec;
  std::vector<preons> preonsVec;
public:
  StarMap();
  StarMap(std::string xmldirectory);
  std::vector<ringworld> getRingworlds();
  std::vector<Resource> getAllBestResources();
  std::vector<Resource> findBestResource(std::string resource);
  std::string getResourceParameter(Resource resource, std::string parameter);
  int getNumberOfSystems();
  int getNumberOfSectors();
};
