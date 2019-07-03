#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Utilities.h"
GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)

{
}

bool GameState::update(sf::Time dt)
{
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
	sf::RenderWindow& window = *getContext().window;
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(100, 220));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(100, 100);

	window.draw(shape);
}