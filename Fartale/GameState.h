#pragma once
#include "State.h"
#include "World.h"
#include <SFML/Graphics/Texture.hpp>
class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	virtual void draw();

private:
	World mWorld;
};
