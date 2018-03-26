#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "StarMap.h"
#include "cli.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    string filename(argv[1]);
    StarMap map(filename);
    startCli(map);

  } else {

    //debug
    StarMap map("C:/Users/Guillermo/Desktop/Blackstone Corporation Star Map.xml");
    startCli(map);
    //end debug

    cout << "No xml found. Drag and drop the star map onto the exe." << endl;
    string temp;
    cin >> temp;
    return 0;
  }

  /*
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
  */
}
