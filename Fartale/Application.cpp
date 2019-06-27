#include "Application.h"

Application::Application()
	: mWindow(sf::VideoMode(1280, 720), "Fartale", sf::Style::Close)
	, mStatisticsFrames(0)
	, mStatisticsUpdateTime(sf::Time::Zero)
{
	mFonts.load("assets/Fonts/main.ttf", Fonts::MAIN);

	mStatisticsFPS.setFont(mFonts.get(Fonts::MAIN));
	mStatisticsFPS.setCharacterSize(12);
	mStatisticsFPS.setPosition(5, 5);
}

void Application::run()
{
	sf::Clock clock;
	const sf::Time timePerUpdate = sf::seconds(1.f / 60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {
		sf::Time dT = clock.restart();
		timeSinceLastUpdate += dT;
		while (timeSinceLastUpdate > timePerUpdate)
		{
			timeSinceLastUpdate -= timePerUpdate;

			processEvents();
			update(timePerUpdate);
		}
		updateStatistics(dT);
		render();
	}
}

void Application::update(sf::Time dT)
{
}

void Application::processEvents()
{
}

void Application::render()
{
}

void Application::updateStatistics(sf::Time dT)
{
	mStatisticsUpdateTime += dT;
	mStatisticsFrames += 1;
	if (mStatisticsUpdateTime.asSeconds > sf::seconds(1)) {
		mStatisticsFPS.setString("FPS: " + toString(mStatisticsFPS));

		mStatisticsUpdateTime = sf::Time::Zero;
		mStatisticsFrames = 0;
	}
}