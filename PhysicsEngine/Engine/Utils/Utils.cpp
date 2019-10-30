#include "Utils.h"

std::string Utils::GenerateHex(const unsigned int len) {
	std::stringstream ss;
	for (auto i = 0; i < len; i++) {
		const auto rc = Utils::RandomChar();
		std::stringstream hexstream;
		hexstream << std::hex << int(rc);
		auto hex = hexstream.str();
		ss << (hex.length() < 2 ? '0' + hex : hex);
	}
	return ss.str();
}


unsigned char Utils::RandomChar() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);

	return static_cast<unsigned char>(dis(gen));
}

const char* Utils::ReadFile(char* file) {
	std::ifstream f(file);
	if (!f.good())
		return "";
	std::stringstream str;
	if (f.is_open())
	{
		while (f.peek() != EOF)
		{
			str << (char)f.get();
		}
		f.close();
		std::string s = str.str();
		const char* c_s = strdup(s.c_str());
		return c_s;
	}
}
