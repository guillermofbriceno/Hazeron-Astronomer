#include <string>
#include <vector>
#include <fstream>

#include "elements.h"

using namespace std;

string getParameter(string line, string tag) {
  tag = tag + "=";
  if (line.find(tag) != string::npos) {
    int posf = line.find(tag);
    posf += tag.length() + 1;
    int posl = line.find("\"", posf);
    return line.substr(posf, (posl - posf));
  } else {
    return "-1";
  }
}

elements parseMap(string xmldirectory) {
  ifstream file(xmldirectory);
  vector<galaxy> galaxyVec;
  vector<sector> sectorVec;
  vector<sys> sysVec;
  vector<star> starVec;
  vector<planet> planetVec;
  vector<Resource> resourceVec;
  vector<preons> preonsVec;

  while(!file.eof()) {
    string line = "";
    getline(file, line);

    if (line.find("<galaxy") != string::npos) {
      galaxy gal;
      gal.name = getParameter(line, "name");
      galaxyVec.push_back(gal);
    }

    if (line.find("<sector") != string::npos) {
      sector sec;
      sec.sectorId = getParameter(line, "sectorId");
      sec.name = getParameter(line, "name");
      sec.x = getParameter(line, "x");
      sec.y = getParameter(line, "y");
      sec.z = getParameter(line, "z");
      sec.sys = sysVec.size();
      sec.galaxy = galaxyVec.size() - 1;
      sectorVec.push_back(sec);
    }

    if (line.find("<system") != string::npos) {
      string eod = getParameter(line, "eod");
      if (eod == "Surveyed") {
        sys s;
        s.systemId = getParameter(line, "systemId");
        s.name = getParameter(line, "name");
        s.x = getParameter(line, "x");
        s.y = getParameter(line, "y");
        s.z = getParameter(line, "z");
        s.star = starVec.size();
        s.planet = planetVec.size();
        s.sector = sectorVec.size() - 1;

        sysVec.push_back(s);
      }
    }

    if (line.find("<star") != string::npos) {
      star s;
      s.starId = getParameter(line, "starId");
      s.name = getParameter(line, "name");
      s.orbit = getParameter(line, "orbit");
      s.spectralClass = getParameter(line, "spectralClass");
      s.size = getParameter(line, "size");
      s.hab = getParameter(line, "hab");
      s.shell = getParameter(line, "shell");
      s.diameter = getParameter(line, "diameter");
      s.preons = preonsVec.size();
      s.sys = sysVec.size() - 1;
      starVec.push_back(s);
    }

    if (line.find("<planet") != string::npos) {
      planet plan;
      plan.planetId = getParameter(line, "planetId");
      plan.name = getParameter(line, "name");
      plan.bodyType = getParameter(line, "bodyType");
      plan.orbit = getParameter(line, "orbit");
      plan.zone = getParameter(line, "zone");
      plan.resource = resourceVec.size();
      plan.sys = sysVec.size() - 1;
      planetVec.push_back(plan);
    }

    if (line.find("<resource") != string::npos) {
      if (line.find("Preons") != string::npos) {
        preons p;
        p.name = getParameter(line, "name");
        p.quality = stoi(getParameter(line, "quality"));
        p.abundance = stoi(getParameter(line, "abundance"));
        p.star = starVec.size() - 1;
        preonsVec.push_back(p);
      } else {
        int planetIndex = planetVec.size() - 1;
        string n = getParameter(line, "name");
        int q1 = stoi(getParameter(line, "qualityZone1"));
        int a1 = stoi(getParameter(line, "abundanceZone1"));
        int q2 = stoi(getParameter(line, "qualityZone2"));
        int a2 = stoi(getParameter(line, "abundanceZone2"));
        int q3 = stoi(getParameter(line, "qualityZone3"));
        int a3 = stoi(getParameter(line, "abundanceZone3"));

        int zones = 0;
        int qarray[3] = {q1, q2, q3};
        int aarray[3] = {a1, a2, a3};
        if (q3 != -1) {
          zones = 3;
        } else if (q2 != -1) {
          zones = 2;
        } else {
          zones = 1;
        }

        Resource rec(planetIndex, n, qarray, aarray, zones);

        resourceVec.push_back(rec);
      }
    }
  }

  file.close();

  elements el;
  el.galaxyVec = galaxyVec;
  el.sectorVec = sectorVec;
  el.sysVec = sysVec;
  el.starVec = starVec;
  el.planetVec = planetVec;
  el.resourceVec = resourceVec;
  el.preonsVec = preonsVec;

  return el;
}
