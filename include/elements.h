#pragma once

#include <string>
#include <vector>

struct Resource {
  int planet;
  std::string name;
  int quality[3];
  int abundance[3];
  int zones;
  int highestQl;
  int highestZone;
  int identifier;
  int selection;

  Resource(int p, std::string n, int q[3], int a[3], int z);
};

struct preons {
  std::string name;
  int quality;
  int abundance;
  int star;
};

struct planet {
  std::string planetId;
  std::string name;
  std::string bodyType;
  std::string orbit;
  std::string zone;
  bool isHabitableEnvironment;
  int resource;
  int sys;
};

struct star {
  std::string starId;
  std::string name;
  std::string orbit;
  std::string spectralClass;
  std::string size;
  std::string hab;
  std::string shell;
  std::string diameter;
  bool habitableWithinOneAu;
  float habitableDistance;
  int preons;
  int sys;
};

struct sys {
  std::string systemId;
  std::string name;
  std::string x;
  std::string y;
  std::string z;
  std::string eod;
  int star;
  int planet;
  int sector;
};

struct sector {
  std::string sectorId;
  std::string name;
  std::string x;
  std::string y;
  std::string z;
  int sys;
  int galaxy;
};

struct galaxy {
  std::string name;
};

struct ringworld {
  std::string name;
  std::string orbit;
  int resource;
  int sys;
  int arcs;
  ringworld(std::string n, std::string o, int r, int sy, int a) {
    name = n;
    orbit = o;
    resource = r;
    sys = sy;
    arcs = a;
  }
};

struct elements {
  std::vector<galaxy> galaxyVec;
  std::vector<sector> sectorVec;
  std::vector<sys> sysVec;
  std::vector<star> starVec;
  std::vector<planet> planetVec;
  std::vector<Resource> resourceVec;
  std::vector<preons> preonsVec;
  int potentialRingworlds;
};
