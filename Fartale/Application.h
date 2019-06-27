#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Utilities.h"
#include "ResourceIdentifiers.h"

class Application
{
public:
	Application();

	void run();
	void update(sf::Time dT);
	void processEvents();
	void render();

	void updateStatistics(sf::Time dT);

private:
	sf::RenderWindow mWindow;

	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsFrames;
	sf::Text mStatisticsFPS;

	FontManager mFonts;
	TextureManager mTextures;
};
