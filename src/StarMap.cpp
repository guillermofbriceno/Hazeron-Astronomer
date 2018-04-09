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
  potentialRingworlds = el.potentialRingworlds;
}

//generates a vector of the first instance of every ringworld.
vector<ringworld> StarMap::getRingworlds() {
  vector<ringworld> ringworldVector;
  string currentName = "nothing";
  for (const auto& x : planetVec ) {
    if (x.bodyType.find("Ringworld Arc") != string::npos) {
      if (x.name.find(currentName) == string::npos) {
        ringworld temp(x.name, x.orbit, x.resource,
            x.sys, 1);
        ringworldVector.push_back(temp);
        currentName = x.name;
        currentName = currentName.substr(0, currentName.length() - 5);
        ringworldVector.back().name = currentName;
      } else {
        ringworldVector.back().arcs++;
      }
    }
  }

  return ringworldVector;
}

//generates a vector of all of the highest quality resources in the map.
vector<Resource> StarMap::getAllBestResources() const {
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

string StarMap::getResourceParameter(Resource resource, const string& parameter) const {
  if (parameter == "Galaxy"){
    int p = resource.planet;
    int sy = planetVec.at(p).sys;
    int se = sysVec.at(sy).sector;
    int ga = sectorVec.at(se).galaxy;
    return galaxyVec.at(ga).name;
  } else if (parameter == "Sector"){
    int p = resource.planet;
    int sy = planetVec.at(p).sys;
    int se = sysVec.at(sy).sector;
    string sec;
    if (sectorVec.at(se).name == "Sector")
      sec = sectorVec.at(se).x + "," + sectorVec.at(se).y + "," + sectorVec.at(se).z;
    else
      sec = sectorVec.at(se).name;

    return sec;
  } else if (parameter == "System") {
    int p = resource.planet;
    int sy = planetVec.at(p).sys;
    return sysVec.at(sy).name;
  } else if (parameter == "Zone") {
    return to_string(resource.highestZone);
  } else if (parameter == "Quality") {
    return to_string(resource.highestQl);
  } else if (parameter == "Abundance") {
    int abun = resource.abundance[resource.highestZone - 1];
    return to_string(abun);
  } else if (parameter == "Planet") {
    int p = resource.planet;
    return planetVec.at(p).name;
  } else if (parameter == "Name") {
    if (resource.name == "Water in the Environment") {
      return "Water";
    } else if (resource.name == "Antiflux Particles") {
      return "Antiflux";
    } else if (resource.name == "Vegetation Density") {
      return "Vegetation Den.";
    } else if (resource.name == "Borexino Precipitate") {
      return "Borexino Prec.";
    } else {
      return resource.name;
    }
  }

  return "Invalid Parameter in function getResourceParameter()";
}

string StarMap::getRingworldParameter(ringworld ringworld, string parameter) const {
  if (parameter == "Galaxy"){
    int sy = ringworld.sys;
    int se = sysVec.at(sy).sector;
    int ga = sectorVec.at(se).galaxy;
    return galaxyVec.at(ga).name;
  } else if (parameter == "Sector"){
    int sy = ringworld.sys;
    int se = sysVec.at(sy).sector;
    string sec;
    if (sectorVec.at(se).name == "Sector")
      sec = sectorVec.at(se).x + "," + sectorVec.at(se).y + "," + sectorVec.at(se).z;
    else
      sec = sectorVec.at(se).name;

    return sec;
  } else if (parameter == "System") {
    int sy = ringworld.sys;
    return sysVec.at(sy).name;
  } else if (parameter == "Name") {
    return ringworld.name;
  } else if (parameter == "Arcs") {
    return to_string(ringworld.arcs);
  }

  return "Invalid Parameter in function getResourceParameter()";
}

int StarMap::getNumberOfSystems() const {
  return sysVec.size();
}

int StarMap::getNumberOfSectors() const {
  return sectorVec.size();
}

int StarMap::getPotentialRingworlds() const {
  return potentialRingworlds;
}
