#include <string>

#include "elements.h"

using namespace std;

Resource::Resource(int p, string n, int q[3], int a[3], int z) {
  planet = p;
  name = n;
  zones = z;
  identifier = 0;
  selection = 0;
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
