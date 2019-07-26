#pragma once
#include "SceneNode.h"
class Entity : public SceneNode
{
public:
	Entity(int hitPoints);

	void setVelocity(sf::Vector2f newVelocity);
	void setVelocity(float vX, float vY);
	sf::Vector2f getVelocity() const;

	void accelerate(sf::Vector2f v);
	void accelerate(float vX, float vY);

	void damage(int points);
	void heal(int points);

	int getHitpoints()const;

protected:
	virtual void updateCurrent(sf::Time dT);
private:
	int mHitPoints;
	sf::Vector2f mVelocity;
};
