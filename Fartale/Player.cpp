#include "Player.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Player::Player(TextureManager& textures)
	: Entity(100)
	, mSprite(textures.get(Textures::PlayerSheet))
{
}

unsigned int Player::getCategory() const
{
	return Category::PLAYER;
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mSprite, states);
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(getBoundingRect().width, getBoundingRect().height));
	box.setFillColor(sf::Color::Transparent);
	box.setPosition(getPosition());

	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(0.6);
	//target.draw(box);
}

void Player::updateCurrent(sf::Time dT)
{
	Entity::updateCurrent(dT); //moving
}
sf::FloatRect Player::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}