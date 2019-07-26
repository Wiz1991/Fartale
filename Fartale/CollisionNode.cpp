#include "CollisionNode.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
CollisionNode::CollisionNode(const sf::FloatRect mask)
	: mCollisionMask(mask)
{
}

unsigned int CollisionNode::getCategory() const
{
	return Category::COLLISIONBLOCK;
}

sf::FloatRect CollisionNode::getBoundingRect() const
{
	return mCollisionMask;
}

void CollisionNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(mCollisionMask.width, mCollisionMask.height));
	box.setFillColor(sf::Color::Transparent);
	box.setPosition(getPosition());

	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(0.6);

	target.draw(box, states);
}