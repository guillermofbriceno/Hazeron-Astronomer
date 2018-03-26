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

    /*debug
    StarMap map("C:/Users/Guillermo/Desktop/Blackstone Corporation Star Map.xml");
    startCli(map);
    end debug */

    cout << "No xml found. Drag and drop the star map onto the exe." << endl;
    string temp;
    cin >> temp;
    return 0;
  }
}
