#pragma once
#include "ResourceHolder.h"
namespace sf {
	class Texture;
	class Font;
}
namespace Textures {
	enum ID {
		blueButtons
	};
}
namespace Fonts {
	enum ID {
		MAIN,
	};
}
typedef ResourceHolder<Textures::ID, sf::Texture> TextureManager;
typedef ResourceHolder<Fonts::ID, sf::Font> FontManager;