#include "MenuState.h"
#include <SFML/Graphics/RenderWindow.hpp>

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackground(context.textureHolder->get(Textures::blueButtons))
{
}

bool MenuState::update(sf::Time dT)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	return true;
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackground);
}