#pragma once
#include "SceneNode.h"

namespace sf {
	class RectangleShape;
}
class CollisionNode : public SceneNode
{
public:
	CollisionNode(const sf::FloatRect mask);
	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	sf::FloatRect mCollisionMask;
};
