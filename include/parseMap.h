#pragma once

#include <string>
#include "elements.h"

std::string getParameter(std::string line, std::string tag);
elements parseMap(std::string xmldirectory);
