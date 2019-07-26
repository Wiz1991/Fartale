#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class SpriteNode : public SceneNode
{
public:
	SpriteNode(const sf::Texture& texture);
	SpriteNode(sf::Texture& texture, sf::IntRect textureRectangle);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};
