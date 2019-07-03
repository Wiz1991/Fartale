#pragma once
#include <sstream>
namespace sf {
	class Sprite;
	class Text;
}

template<typename T>
std::string toString(T value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);