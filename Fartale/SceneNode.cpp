#include "SceneNode.h"

SceneNode::SceneNode(Layers category)
	: mParent(nullptr)
	, mChildren()
	, mCategory(category)
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