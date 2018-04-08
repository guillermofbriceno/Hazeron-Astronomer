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
  std::vector<galaxy> galaxyVec;
  std::vector<sector> sectorVec;
  std::vector<sys> sysVec;
  std::vector<star> starVec;
  std::vector<planet> planetVec;
  std::vector<Resource> resourceVec;
  std::vector<preons> preonsVec;
  int potentialRingworlds;
public:
  StarMap();
  StarMap(std::string xmldirectory);
  std::vector<ringworld> getRingworlds();
  std::vector<Resource> getAllBestResources() const;
  std::vector<Resource> findBestResource(std::string resource);
  std::string getResourceParameter(Resource resource, const std::string& parameter) const;
  std::string getRingworldParameter(ringworld ringworld, std::string parameter) const;
  int getNumberOfSystems() const;
  int getNumberOfSectors() const;
  int getPotentialRingworlds() const;
};
