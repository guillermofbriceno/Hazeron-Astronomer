#pragma once

#include <string>
#include "elements.h"

std::string getParameter(const std::string& line, std::string tag);
elements parseMap(const std::string& xmldirectory);
