#include "SpriteNode.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
}

SpriteNode::SpriteNode(sf::Texture& texture, sf::IntRect textureRectangle)
	: mSprite(texture, textureRectangle)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mSprite, states);
}