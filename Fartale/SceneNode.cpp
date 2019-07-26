#include "SceneNode.h"
#include "Command.h"
SceneNode::SceneNode(Category::Type category)
	: mParent(nullptr)
	, mChildren()
	, mDefaultCategory(category)
{
}

void SceneNode::attachNode(Ptr node)
{
	node->mParent = this;

	mChildren.push_back(std::move(node));
}

void SceneNode::detachNode(Ptr& node)
{
}

void SceneNode::update(sf::Time dT)
{
	updateCurrent(dT);

	updateChildren(dT);
}

void SceneNode::updateCurrent(sf::Time dT)
{
	//default
}

void SceneNode::updateChildren(sf::Time dT)
{
	updateCurrent(dT);

	for (auto& child : mChildren) {
		child->update(dT);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawCurrent(target, states);

	for (auto& child : mChildren) {
		child->draw(target, states);
	}
}
sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}
sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs, sf::FloatRect view)
{
	if (view.contains(sceneGraph.getPosition()))
		checkNodeCollision(sceneGraph, collisionPairs, view);

	for (Ptr& child : sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs, view);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs, sf::FloatRect view)
{
	if (view.contains(node.getPosition()))
		if (this != &node && collision(*this, node))
			collisionPairs.insert(std::minmax(this, &node));

	for (Ptr& child : mChildren)
		child->checkNodeCollision(node, collisionPairs, view);
}

void SceneNode::onCommand(const Command& command, sf::Time dT)
{
	if (command.category & getCategory()) {
		command.action(*this, dT);
	}
	for (auto& child : mChildren)
		child->onCommand(command, dT);
}

unsigned int SceneNode::getCategory() const
{
	return mDefaultCategory;
}
bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}