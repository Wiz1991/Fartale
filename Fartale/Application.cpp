#include "Application.h"
#include "Utilities.h"

Application::Application()
	: mWindow(sf::VideoMode(1280, 720), "Fartale", sf::Style::Close)
	, mStatisticsFrames(0)
{
	mFonts.load("assets/Fonts/main.ttf", Fonts::MAIN);

	mStatisticsText.setFont(mFonts.get(Fonts::MAIN));
	mStatisticsText.setCharacterSize(12);
	mStatisticsText.setPosition(5, 5);
	mStatisticsText.setFillColor(sf::Color::Black);
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
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::render()
{
	mWindow.clear(sf::Color::White);

	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dT)
{
	mStatisticsUpdateTime += dT;
	mStatisticsFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1)) {
		mStatisticsText.setString("FPS: " + toString(mStatisticsFrames));

		mStatisticsUpdateTime = sf::Time::Zero;
		mStatisticsFrames = 0;
	}
}