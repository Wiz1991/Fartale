#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Utilities.h"
GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fontHolder)

{
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == Key::ESC)
		requestStackPush(States::PAUSED);

	return true;
}

void GameState::draw()
{
	mWorld.draw();
}