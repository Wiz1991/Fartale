#pragma once
#include "State.h"
#include <SFML/Graphics/Sprite.hpp>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual bool update(sf::Time dT);
	virtual bool handleEvent(const sf::Event& event);
	virtual void draw();

private:
	sf::Sprite mBackground;
};
