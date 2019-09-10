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
