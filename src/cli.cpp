#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "StarMap.h"
#include "cli.h"

using namespace std;

void startCli(StarMap &map) {
  cout << map.getNumberOfSystems() << " surveyed systems found over "
       << map.getNumberOfSectors() << " sectors." << endl;

  while (true) {
    cout << endl << "-> ";
    string command;
    getline(cin, command);
    cout << endl;

    istringstream iss(command);
    vector<string> result{
      istream_iterator<string>(iss), {}
    };

    for (unsigned int i = 0; i < result.size(); i++) {
      for (unsigned int j = 0; j < result.at(i).length(); j++)
        result.at(i)[j] = tolower(result.at(i)[j]);
    }

    if (result.at(0) == "find") {
      find(result.at(1), map);
    }
  }
}

void find(string resource, StarMap &map) {
  vector<Resource> bestResults;
  bestResults = map.findBestResource(resource);

}
