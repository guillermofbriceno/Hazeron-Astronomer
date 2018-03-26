#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "elements.h"
#include "parseMap.h"
#include "StarMap.h"

using namespace std;

StarMap::StarMap() {}

StarMap::StarMap(string xmldirectory) {
  elements el = parseMap(xmldirectory);
  galaxyVec = el.galaxyVec;
  sectorVec = el.sectorVec;
  sysVec = el.sysVec;
  starVec = el.starVec;
  planetVec = el.planetVec;
  resourceVec = el.resourceVec;
  preonsVec = el.preonsVec;
}

//generates a vector of the first instance of every ringworld.
vector<ringworld> StarMap::getRingworlds() {
  vector<ringworld> ringworldVector;
  string currentName = "nothing";
  for (unsigned int i = 0; i < planetVec.size(); i++) {
    if (planetVec.at(i).bodyType.find("Ringworld Arc") != string::npos) {
      if (planetVec.at(i).name.find(currentName) == string::npos) {
        ringworld temp(planetVec.at(i).name, planetVec.at(i).orbit, planetVec.at(i).resource,
            planetVec.at(i).sys, 1);
        ringworldVector.push_back(temp);
        currentName = planetVec.at(i).name;
        currentName = currentName.substr(0, currentName.length() - 1);
      } else {
        ringworldVector.back().arcs++;
      }
    }
  }

  return ringworldVector;
}

//generates a vector of all of the highest quality resources in the map.
vector<Resource> StarMap::getAllBestResources() {
  vector<Resource> bestResults;
  for (unsigned int i = 0; i < resourceVec.size(); i++) {
    bool alreadyExists = false;
    if (bestResults.empty()) {
      bestResults.push_back(resourceVec.at(i));
    } else {
      for (unsigned int j = 0; j < bestResults.size(); j++) {
        if (bestResults.at(j).name == resourceVec.at(i).name) {
          if (bestResults.at(j).highestQl < resourceVec.at(i).highestQl) {
            bestResults.at(j) = resourceVec.at(i);
          }
          alreadyExists = true;
        }
      }
      if (!alreadyExists)
        bestResults.push_back(resourceVec.at(i));
    }
  }

  return bestResults;
}

vector<Resource> StarMap::findBestResource(string resource) {
  resource[0] = toupper(resource[0]);
  vector<Resource> bestResults;
  int top = 0;
  for (unsigned int i = 0; i < resourceVec.size(); i++) {
    if (resourceVec.at(i).name.find(resource) != string::npos) {
      if (resourceVec.at(i).highestQl > top) {
        top = resourceVec.at(i).highestQl;
      }
    }
  }
  for (unsigned int i = 0; i < resourceVec.size(); i++) {
    if (resourceVec.at(i).name.find(resource) != string::npos) {
      if (resourceVec.at(i).highestQl == top) {
        bestResults.push_back(resourceVec.at(i));
      }
    }
  }

  return bestResults;
}

string StarMap::getResourceParameter(Resource resource, string parameter) {
  if (parameter == "galaxy"){
    int p = resource.planet;
    int sy = planetVec.at(p).sys;
    int se = sysVec.at(sy).sector;
    int ga = sectorVec.at(se).galaxy;
    return galaxyVec.at(ga).name;
  } else if (parameter == "sector"){
    int p = resource.planet;
    int sy = planetVec.at(p).sys;
    int se = sysVec.at(sy).sector;
    string sec;
    if (sectorVec.at(se).name == "Sector")
      sec = sectorVec.at(se).x + "," + sectorVec.at(se).y + "," + sectorVec.at(se).z;
    else
      sec = sectorVec.at(se).name;

    return sec;
  } else if (parameter == "system") {
    int p = resource.planet;
    string planet = planetVec.at(p).name;
    int sy = planetVec.at(p).sys;
    return sysVec.at(sy).name;
  } else if (parameter == "zone") {
    int abun = resource.abundance[resource.highestZone - 1];
    return to_string(abun);
  }

  return "Invalid Parameter in function getResourceParameter()";
}

int StarMap::getNumberOfSystems() {
  return sysVec.size();
}

int StarMap::getNumberOfSectors() {
  return sectorVec.size();
}