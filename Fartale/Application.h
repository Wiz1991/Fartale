#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateStack.h"
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();

	void run();
private:
	void update(sf::Time dT);
	void processEvents();
	void render();

	void updateStatistics(sf::Time dT);

	void registerStates();

private:
	sf::RenderWindow mWindow;

	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsFrames;
	sf::Text mStatisticsText;

	FontManager mFonts;
	TextureManager mTextures;

	StateStack mStateStack;
};
