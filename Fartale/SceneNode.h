#pragma once
#include <SFML/System/Time.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>
#include <vector>
#include "SceneCategories.h"

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	explicit SceneNode(Layers category = Layers::NONE);

	void attachNode(Ptr node);
	void detachNode(Ptr& node);

	void update(sf::Time dT);

private:
	virtual void updateCurrent(sf::Time dT);
	void updateChildren(sf::Time dT);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	Layers mCategory;
};
