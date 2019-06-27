#pragma once
#include "ResourceHolder.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
namespace Textures {
	enum ID {
	};
}
namespace Fonts {
	enum ID {
		MAIN,
	};
}
typedef ResourceHolder<Textures::ID, sf::Texture> TextureManager;
typedef ResourceHolder<Fonts::ID, sf::Font> FontManager;