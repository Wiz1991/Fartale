#pragma once
#include "State.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Container.h"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual bool update(sf::Time dT);
	virtual bool handleEvent(const sf::Event& event);
	virtual void draw();
private:
	sf::RectangleShape overlay;

	Container mGUIContainer;
};
