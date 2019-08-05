#pragma once
#include <SFML/System/Time.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>
#include <vector>
#include "SceneCategories.h"
#include <set>
#include "Command.h"

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	explicit SceneNode(Category::Type category = Category::Type::NONE);

	void attachNode(Ptr node);
	void detachNode(Ptr& node);

	void update(sf::Time dT);

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual unsigned int getCategory() const;

	void checkSceneCollision(SceneNode& sceneGraph, std::vector<Pair>& collisionPairs, sf::FloatRect view);
	void checkNodeCollision(SceneNode& node, std::vector<Pair>& collisionPairs, sf::FloatRect view);

	void onCommand(const Command& command, sf::Time dT);
private:
	virtual void updateCurrent(sf::Time dT);
	void updateChildren(sf::Time dT);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	Category::Type mDefaultCategory;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);
