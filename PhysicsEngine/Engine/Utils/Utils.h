#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <string>
#include <fstream>

class Utils
{
public:

	static std::string GenerateHex(const unsigned int len);
	static unsigned char RandomChar();
	static const char* ReadFile(char* file);
};

