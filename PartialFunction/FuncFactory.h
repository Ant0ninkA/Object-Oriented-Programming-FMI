#pragma once
#include <iostream>
#include <fstream>
#include "PartialFunc.h"

PartialFunc* funcFactory(std::ifstream& is);

char* readFromBinaryFile(std::ifstream& is);
