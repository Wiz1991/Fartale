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

void centerOrigin(sf::Sprite& sprite) {
	sf::FloatRect size = sprite.getLocalBounds();
	sprite.setOrigin(size.width / 2, size.height / 2);
}
void centerOrigin(sf::Text& text) {
	sf::FloatRect size = text.getLocalBounds();
	text.setOrigin(size.width / 2, size.height / 2);
}