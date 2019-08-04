#include "Entity.h"
#include <cmath>

Entity::Entity(int hitPoints)
	: mHitPoints(hitPoints)
	, mVelocity(0, 0)
	, gravity(64)
	, falling(true)
	, jumping(false)
{
}

void Entity::setVelocity(sf::Vector2f newVelocity)
{
	mVelocity = newVelocity;
}

void Entity::setVelocity(float vX, float vY)
{
	mVelocity.x = vX;
	mVelocity.y = vY;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f v)
{
	mVelocity += v;
}

void Entity::accelerate(float vX, float vY)
{
	mVelocity.x += vX;
	mVelocity.y += vY;
}

void Entity::damage(int points)
{
	std::max(0, mHitPoints -= points);
}

void Entity::heal(int points)
{
	mHitPoints += points;
}

int Entity::getHitpoints() const
{
	return mHitPoints;
}

void Entity::updateCurrent(sf::Time dT)
{
	if (jumping) {
		gravity -= 600;
		mVelocity.y = -gravity;
		if (gravity <= 0) {
			jumping = false;
			falling = true;
		}
	}
	if (falling) {
		gravity += 5;
		mVelocity.y = gravity;
	}
	move(mVelocity * dT.asSeconds());
}