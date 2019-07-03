#include "Application.h"
#include "Utilities.h"
#include "MenuState.h"

Application::Application()
	: mWindow(sf::VideoMode(1280, 720), "Fartale", sf::Style::Close)
	, mStatisticsFrames(0)
	, mStateStack(State::Context(mWindow, mTextures, mFonts))
{
	mFonts.load("assets/Fonts/main.ttf", Fonts::MAIN);
	mTextures.load("assets/Textures/UIpack/Spritesheet/blueSheet.png", Textures::blueButtons);

	mStatisticsText.setFont(mFonts.get(Fonts::MAIN));
	mStatisticsText.setCharacterSize(12);
	mStatisticsText.setPosition(5, 5);
	mStatisticsText.setFillColor(sf::Color::Black);

	registerStates();
	mStateStack.pushState(States::MENU);
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

			if (mStateStack.isEmpty())
				mWindow.close();
		}
		updateStatistics(dT);
		render();
	}
}

void Application::update(sf::Time dT)
{
	mStateStack.update(dT);
}

void Application::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		mStateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::render()
{
	mWindow.clear(sf::Color::White);

	mStateStack.draw();
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

void Application::registerStates()
{
	mStateStack.registerState<MenuState>(States::MENU);
}