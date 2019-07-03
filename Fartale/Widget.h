#pragma once
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace sf {
	class Event;
}
class Widget : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::shared_ptr<Widget> Ptr;
	Widget();

	virtual bool isSelectable() const = 0;
	bool isSelected() const;

	virtual void select();
	virtual void deselect();

	virtual void activate();
	virtual void deactivate();

	virtual bool isActive() const;

	virtual void handleEvent(const sf::Event& event) = 0;

private:
	bool mIsSelected;
	bool mIsActive;
};
