#pragma once
#include "SceneNode.h"
#include <array>
#include "SceneCategories.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

namespace sf {
	class RenderWindow;
	class Time;
	class Event;
}

class World
{
public:
	World(sf::RenderWindow& window, FontManager& fonts);

	void update(sf::Time dT);
	void draw();

private:
	void buildScene();

private:
	sf::RenderWindow& mWindow;

	std::array<SceneNode*, Layers::TOTAL> mSceneLayers;
	SceneNode mSceneGraph;

	TextureManager mTextures;
	FontManager& mFonts;
};
