#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iomanip>

using namespace std;

class Resource {
public:
  int planet;
  string name;
  int quality[3];
  int abundance[3];
  int zones;
  int highestQl;
  int highestZone;

  Resource(int p, string n, int q[3], int a[3], int z) {
    planet = p;
    name = n;
    zones = z;
    if (zones == 1) {
      highestZone = 1;
      highestQl = q[0];
      quality[0] = q[0];
      abundance[0] = a[0];
    } else {
      highestQl = 0;
      for (int i = 0; i < zones; i++) {
        quality[i] = q[i];
        abundance[i] = a[i];
        if (quality[i] > highestQl) {
          highestQl = quality[i];
          highestZone = i + 1;
        }
      }
    }
  }
};

struct preons {
  string name;
  int quality;
  int abundance;
  int star;
};

struct planet {
  string planetId;
  string name;
  string bodyType;
  string orbit;
  string zone;
  int resource;
  int sys;
};

struct star {
  string starId;
  string name;
  string orbit;
  string spectralClass;
  string size;
  string hab;
  string shell;
  string diameter;
  int preons;
  int sys;
};

struct sys {
  string systemId;
  string name;
  string x;
  string y;
  string z;
  string eod;
  int star;
  int planet;
  int sector;
};

struct sector {
  string sectorId;
  string name;
  string x;
  string y;
  string z;
  int sys;
  int galaxy;
};

struct galaxy {
  string name;
};

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

int main() {
  ifstream file("Blackstone Corporation Star Map.xml");

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

  int numSys = sysVec.size();
  int numSec = sectorVec.size();

  cout << numSys << " surveyed systems found over " << numSec << " sectors." << endl;

  while (true) {
    cout << endl << "-> ";
    string command;
    getline(cin, command);
    cout << endl;

    istringstream iss(command);
    vector<string> result{
      istream_iterator<string>(iss), {}
    };

    for (int i = 0; i < result.size(); i++) {
      for (int j = 0; j < result.at(i).length(); j++)
        result.at(i)[j] = tolower(result.at(i)[j]);
    }

    if ((result.at(0).find("ringworld") != string::npos) && result.size() == 1) {
      vector<planet> ringworldVector;
      vector<int> arcVector;
      string currentName = "nothing";
      for (int i = 0; i < planetVec.size(); i++) {
        if (planetVec.at(i).bodyType.find("Ringworld Arc") != string::npos) {
          if (planetVec.at(i).name.find(currentName) == string::npos) {
            ringworldVector.push_back(planetVec.at(i));
            currentName = planetVec.at(i).name;
            currentName = currentName.substr(0, currentName.length() - 1);
            int arcs = 1;
            arcVector.push_back(arcs);
          } else {
            arcVector.at(ringworldVector.size() - 1)++;
          }
        }
      }

      int planetWidest = 0;
      for (int i = 0; i < ringworldVector.size(); i++) {
        string planet = ringworldVector.at(i).name;
        if (planet.length() > planetWidest)
          planetWidest = planet.length();
      }

      cout << left
           << setw(20) << "Galaxy"
           << setw(10) << "Sector"
           << setw(15) << "System"
           << setw(planetWidest - 2) << "Ringworld Name"
           << setw(6) << "Arcs"
           << endl;

      for (int i = 0; i < ringworldVector.size(); i++) {
        string planet = ringworldVector.at(i).name;
        planet = planet.substr(0, planet.length() - 5);
        int sy = ringworldVector.at(i).sys;
        string sys = sysVec.at(sy).name;
        int se = sysVec.at(sy).sector;
        string sec;
        if (sectorVec.at(se).name == "Sector")
          sec = sectorVec.at(se).x + "," + sectorVec.at(se).y + "," + sectorVec.at(se).z;
        else
          sec = sectorVec.at(se).name;
        int ga = sectorVec.at(se).galaxy;
        string galaxy = galaxyVec.at(ga).name;

        cout << left
             << setw(20) << galaxy
             << setw(10) << sec
             << setw(15) << sys
             << setw(planetWidest - 2) << planet
             << setw(6) << arcVector.at(i)
             << endl;
      }
    } else if (result.at(0) == "allbest") {
      vector<Resource> bestResults;
      for (int i = 0; i < resourceVec.size(); i++) {
        bool alreadyExists = false;
        if (bestResults.empty()) {
          bestResults.push_back(resourceVec.at(i));
        } else {
          for (int j = 0; j < bestResults.size(); j++) {
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
      cout << left << setw(25) << "Resource" << "Quality" << endl;
      for (int i = 0; i < bestResults.size(); i++) {
        cout << left << setw(25) << bestResults.at(i).name << bestResults.at(i).highestQl << endl;
      }
    } else if (result.at(0) == "exit") {
      return 0;
    } else if (result.at(0) == "help") {
      if (result.size() == 1) {
        cout << "Available commands: " << endl << endl
             << "find       Finds resource with quality constraints." << endl
             << "allbest    Lists the highest quality of every resource found." << endl
             << "ringworld  Lists all ringworlds." << endl
             << "exit       Ends the program." << endl << endl
             << "Type help <command> for detail." << endl;
      } else {
        if (result.at(1) == "find") {
          cout << "find <resource> <best, [quality]>" << endl << endl
               << "\"find coal best\" lists the highest quality coal in the database." << endl
               << "\"find coal 143\" lists all instances of coal with quality 143 or higher." << endl;
        } else if (result.at(1) == "exit") {
          cout << "Do I really need to explain this to you?" << endl;
        } else if (result.at(1) == "allbest") {
          cout << "Lists the highest quality of every resource found. No parameters." << endl;
        } else if (result.at(1) == "ringworld") {
          cout << "Lists all ringworlds. No parameters." << endl;
        }
      }
    } else if (result.at(0) == "find") {                                        //Find command
      string resource = result.at(1);
      resource[0] = toupper(resource[0]);
      vector<Resource> bestResults;
      if (result.at(2) == "best") {                                             //Best
        int top = 0;
        for (int i = 0; i < resourceVec.size(); i++) {
          if (resourceVec.at(i).name.find(resource) != string::npos) {
            if (resourceVec.at(i).highestQl > top) {
              top = resourceVec.at(i).highestQl;
            }
          }
        }
        for (int i = 0; i < resourceVec.size(); i++) {
          if (resourceVec.at(i).name.find(resource) != string::npos) {
            if (resourceVec.at(i).highestQl == top) {
              bestResults.push_back(resourceVec.at(i));
            }
          }
        }
      } else {                                                                   //min quality
        for (int i = 0; i < resourceVec.size(); i++) {
          if (resourceVec.at(i).name.find(resource) != string::npos)
            if (resourceVec.at(i).highestQl >= stoi(result.at(2)))
              bestResults.push_back(resourceVec.at(i));
        }
      }

      int planetWidest = 0;
      for (int i = 0; i < bestResults.size(); i++) {
        int p = bestResults.at(i).planet;
        string planet = planetVec.at(p).name;
        if (planet.length() > planetWidest)
          planetWidest = planet.length();
      }

      cout << left
           << setw(20) << "Galaxy"
           << setw(10) << "Sector"
           << setw(15) << "System"
           << setw(planetWidest + 3) << "Planet"
           << setw(6) << "Zone"
           << setw(9) << "Quality"
           << setw(5) << "Abundance"
           << endl;

      for (int i = 0; i < bestResults.size(); i++) {
        int abun = bestResults.at(i).abundance[bestResults.at(i).highestZone - 1];
        int q = bestResults.at(i).highestQl;
        int zone = bestResults.at(i).highestZone;
        int p = bestResults.at(i).planet;
        string planet = planetVec.at(p).name;
        int sy = planetVec.at(p).sys;
        string sys = sysVec.at(sy).name;
        int se = sysVec.at(sy).sector;
        string sec;
        if (sectorVec.at(se).name == "Sector")
          sec = sectorVec.at(se).x + "," + sectorVec.at(se).y + "," + sectorVec.at(se).z;
        else
          sec = sectorVec.at(se).name;
        int ga = sectorVec.at(se).galaxy;
        string galaxy = galaxyVec.at(ga).name;

        cout << left
             << setw(20) << galaxy
             << setw(10) << sec
             << setw(15) << sys
             << setw(planetWidest + 3) << planet
             << setw(6) << zone
             << setw(9) << q
             << setw(5) << abun
             << endl;
      }
    } else {
      cout << "Command not found." << endl;
    }
  }
}
