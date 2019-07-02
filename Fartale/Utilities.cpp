#include "Utilities.h"
#include <SFML/Graphics/Sprite.hpp>
#include "SFML/Graphics/Text.hpp"

void centerOrigin(sf::Sprite& sprite) {
	sf::FloatRect size = sprite.getLocalBounds();
	sprite.setOrigin(size.width / 2, size.height / 2);
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect size = text.getGlobalBounds();
	text.setOrigin(size.width / 2, size.height / 2);
}