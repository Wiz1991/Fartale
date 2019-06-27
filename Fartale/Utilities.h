#pragma once
#include <string>
#include <sstream>
#include <SFML/Graphics/Sprite.hpp>

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