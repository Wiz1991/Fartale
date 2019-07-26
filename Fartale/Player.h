#pragma once
#include "Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include "ResourceIdentifiers.h"
#include "SFML/Window/Event.hpp"

class Player : public Entity
{
public:

public:
	Player(TextureManager& textures);

	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void updateCurrent(sf::Time dT);
private:
	sf::Sprite mSprite;
};
