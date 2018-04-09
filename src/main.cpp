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
  if (argc == 2) {
    string filename(argv[1]);
    StarMap map(filename);
    startCli(map);

	return 0;

  } else {

    cerr << "No xml found. Drag and drop the star map onto the exe." << endl;

    return 1;
  }
}
