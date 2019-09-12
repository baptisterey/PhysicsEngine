#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <string>

class Utils
{
public:

	static std::string GenerateHex(const unsigned int len);
	static unsigned char RandomChar();
};

