#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Utilities.h"
#include "PlayerController.h"
GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fontHolder)
	, mPlayer(*context.player)
{
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	CommandQueue& queue = mWorld.getWorldCommandQueue();
	mPlayer.handleRealTimeInput(queue);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& queue = mWorld.getWorldCommandQueue();
	mPlayer.handleEvents(event, queue);

	if (event.type == sf::Event::KeyReleased && event.key.code == Key::ESC)
		requestStackPush(States::PAUSED);

	return true;
}

void GameState::draw()
{
	mWorld.draw();
}