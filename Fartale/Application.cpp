#include "Application.h"
#include "Utilities.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

Application::Application()
	: mWindow(sf::VideoMode(1280, 720), "Fartale", sf::Style::Close)
	, mStatisticsFrames(0)
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
	, displayStatistics(false)

{
	mFonts.load("assets/Fonts/main.ttf", Fonts::MAIN);
	mTextures.load("assets/Textures/UIpack/Spritesheet/blueSheet.png", Textures::blueButtons);
	mTextures.load("assets/Textures/Abstract Platformer/PNG/Backgrounds/set3_background.png", Textures::MenuBackground);

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
		if (event.type == sf::Event::KeyReleased && event.key.code == Key::F9)
			displayStatistics = !displayStatistics;
	}
}

void Application::render()
{
	mWindow.clear(sf::Color::White);

	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	if (displayStatistics)
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
	mStateStack.registerState<GameState>(States::GAME);
	mStateStack.registerState<PauseState>(States::PAUSED);
}